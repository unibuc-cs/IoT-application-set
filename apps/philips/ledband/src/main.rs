use warp::{http, Filter};
use std::sync::{Arc, RwLock};
use std::env::args;

type Rgb = [u8; 3];
const NUM_LEDS: usize = 1;
const RGB_WHITE : [u8; 3] = [255, 255, 255];

struct State {
    on: bool,
    leds: [Rgb; NUM_LEDS],
}

impl State {
    fn new() -> Self {
        State {
            on: true,
            leds: [RGB_WHITE; NUM_LEDS],
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

    // GET /leds -> returns [[r, g, b], ...]
    let get_leds = warp::path!("leds")
    .and(warp::get())
    .and(state_filter.clone())
    .map(|state: Safe<State>| {
        let read_state = state.read().unwrap();
        if read_state.on == false { 
            return warp::reply::with_status(warp::reply::json(&"Bulb is off"), http::StatusCode::BAD_REQUEST);
        }

        return warp::reply::with_status(warp::reply::json(&read_state.leds.clone()), http::StatusCode::OK); 
    });

    // GET /leds/:index -> returns [r, g, b]
    let get_led = warp::path!("leds" / usize)
    .and(warp::get())
    .and(state_filter.clone())
    .map(|index: usize, state: Safe<State>| {
        let read_state = state.read().unwrap();
        if read_state.on == false { 
            return warp::reply::with_status(warp::reply::json(&"Bulb is off"), http::StatusCode::BAD_REQUEST);
        }

        return warp::reply::with_status(warp::reply::json(&read_state.leds[index].clone()), http::StatusCode::OK); 
    });

    // POST /leds, json body [[r, g, b], ...] -> returns OK
    let set_leds = warp::path!("leds")
    .and(warp::post())
    .and(warp::body::json())
    .and(state_filter.clone())
    .map(|value: [Rgb; NUM_LEDS], state: Safe<State>| {
        state.write().unwrap().leds.clone_from(&value);
        warp::reply::with_status("OK", http::StatusCode::OK)
    });

    // POST /leds_all, json body [r, g, b] -> returns OK
    let set_leds_all = warp::path!("leds_all")
    .and(warp::post())
    .and(warp::body::json())
    .and(state_filter.clone())
    .map(|value: Rgb, state: Safe<State>| {
        let mut new_leds = [value; NUM_LEDS];
        for i in 0..NUM_LEDS {
            new_leds[i] = value.clone();
        }
        state.write().unwrap().leds.clone_from(&new_leds);

        warp::reply::with_status("OK", http::StatusCode::OK)
    });

    // POST /leds/:index, json body [r, g, b] -> returns OK
    let set_led = warp::path!("leds" / usize)
    .and(warp::post())
    .and(warp::body::json())
    .and(state_filter.clone())
    .map(|index: usize, value: Rgb, state: Safe<State>| {
        state.write().unwrap().leds[index] = value.clone();
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

    let routes = get_on.or(set_on).or(get_leds).or(set_leds).or(set_led).or(get_led).or(set_leds_all);
    
    println!("Listening on http://0.0.0.0:{}", port_int);
    warp::serve(routes)
        .run(([0, 0, 0, 0], port_int))
        .await;
}
