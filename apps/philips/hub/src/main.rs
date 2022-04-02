use warp::{http, Filter};
use std::sync::{Arc, RwLock};
use std::env::args;
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Clone)]
enum DeviceType {
    LEDS = 0,
    BULB = 1,
}

#[derive(Serialize, Deserialize, Clone)]
struct Device {
    type_: DeviceType,
    url: Box<str>,
}

struct State {
    devices: Vec<Device>,
}

impl State {
    fn new() -> Self {
        State {
            devices: Vec::new(),
        }
    }
}

type Safe<T> = Arc<RwLock<T>>;

trait SafeNew {
    fn safe_new() -> Safe<Self>;
}

impl SafeNew for State {
    fn safe_new() -> Safe<Self> {
        Arc::new(RwLock::new(State::new()))
    }
}

#[tokio::main]
async fn main() {
    let state: Safe<State> = State::safe_new();
    let state_filter = warp::any().map(move || state.clone());
    
    let port_str = args().nth(1).unwrap_or("8080".to_string());
    let port_int = port_str.parse::<u16>().unwrap();

    // POST /update_lights, json body [r, g, b] -> returns ok
    // will update all known devices
    let update_lights = warp::path!("update_lights")
        .and(warp::post())
        .and(warp::body::json())
        .and(state_filter.clone())
        .and_then(|value: [u8; 3], state: Safe<State>| async move { update_lights_fn(value, state).await });

    let add_device = warp::path!("add_device")
    .and(warp::post())
    .and(warp::body::json())
    .and(state_filter.clone())
    .map(|device: Device, state: Safe<State>| {
        let mut state_writable = state.write().unwrap();
        state_writable.devices.push(device.clone());
        warp::reply::with_status("OK", http::StatusCode::OK)
    });

    let routes = update_lights.or(add_device);

    println!("Listening on http://0.0.0.0:{}", port_int);
    warp::serve(routes)
        .run(([0, 0, 0, 0], port_int))
        .await;
}

async fn update_lights_fn(value: [u8; 3], state: Safe<State>) -> Result<impl warp::Reply, warp::Rejection> {
    let devices = state.read().unwrap().devices.clone();

    let client = reqwest::Client::new();

    for device in devices {
        let url = match device.type_ {
            DeviceType::LEDS => format!("{}/leds_all", device.url.clone()),
            DeviceType::BULB => format!("{}/rgb", device.url.clone()),
        };

        let resp = client.post(&url)
            .json(&value)
            .send()
            .await;
        
        match resp {
            Ok(resp) => {
                let text = resp.text().await;
                match text {
                    Ok(text_) => println!("Updated {} {}", url, text_),
                    Err(err) => println!("Failed to get resp {} {}", url, err),
                }
            }
            Err(_) => println!("Failed to update {}", device.url),
        };
    }
    
    Ok(warp::reply::with_status("ok", http::StatusCode::OK))
}