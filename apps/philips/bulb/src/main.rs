use warp::{http, Filter};
use std::sync::{Arc, RwLock};
use std::env::args;

const RGB_WHITE : [u8; 3] = [255, 255, 255];

struct State {
    on: bool,
    rgb: [u8; 3],
}

impl State {
    fn new() -> Self {
        State {
            on: true,
            rgb: RGB_WHITE,
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

    // GET /rgb -> returns [r, g, b]
    let get_rgb = warp::path!("rgb")
        .and(warp::get())
        .and(state_filter.clone())
        .map(|state: Safe<State>| {
            let read_state = state.read().unwrap();
            if read_state.on == false { 
                return warp::reply::with_status(warp::reply::json(&"Bulb is off"), http::StatusCode::BAD_REQUEST);
            }

            return warp::reply::with_status(warp::reply::json(&read_state.rgb.clone()), http::StatusCode::OK); 
        });

    // POST /rgb, json body [r, g, b] -> returns OK
    let set_rgb = warp::path!("rgb")
        .and(warp::post())
        .and(warp::body::json())
        .and(state_filter.clone())
        .map(|value: [u8; 3], state: Safe<State>| {
            state.write().unwrap().rgb.clone_from(&value);
            warp::reply::with_status("OK", http::StatusCode::OK)
        });

    // GET /on -> returns true/false
    let get_on = warp::path!("on")
        .and(warp::get())
        .and(state_filter.clone())
        .map(|state: Safe<State>| warp::reply::json(&state.read().unwrap().on.clone()));

    // POST /on, json body true/false -> returns OK
    let set_on = warp::path!("on")
        .and(warp::post())
        .and(warp::body::json())
        .and(state_filter.clone())
        .map(|value: bool, state: Safe<State>| {
            state.write().unwrap().on.clone_from(&value);
            warp::reply::with_status("OK", http::StatusCode::OK)
        });

    let routes = get_rgb.or(set_rgb).or(get_on).or(set_on);
    
    let port_str = args().nth(1).unwrap_or("8080".to_string());
    let port_int = port_str.parse::<u16>().unwrap();

    println!("Listening on http://0.0.0.0:{}", port_int);
    warp::serve(routes)
        .run(([0, 0, 0, 0], port_int))
        .await;
}