use warp::{http, Filter};
use std::env::args;

type Rgb = [u8; 3];
type Image = Vec<Vec<Rgb>>;

#[tokio::main]
async fn main() {
    let hub_url = args().nth(2).unwrap_or("http://localhost:8080".to_string());
    let hub_url_filter = warp::any().map(move || hub_url.clone());

    // POST /processs, json body HxWx3 -> returns ok
    let process_image = warp::path!("process")
        .and(warp::post())
        .and(warp::body::json())
        .and(hub_url_filter.clone())
        .and_then(|image: Image, url: String| async move {
            // TODO: ar trebui sa simulam niste procesari aici
            inform_hub(image[0][0], &url).await
        });
    
    let port_str = args().nth(1).unwrap_or("8080".to_string());
    let port_int = port_str.parse::<u16>().unwrap();

    println!("Listening on http://0.0.0.0:{}", port_int);
    warp::serve(process_image)
        .run(([0, 0, 0, 0], port_int))
        .await;
}

async fn inform_hub(value: [u8; 3], hub_url: &str) -> Result<impl warp::Reply, warp::Rejection> {
    let client = reqwest::Client::new();

    let theurl = format!("{}/update_lights", hub_url);
    let resp = client.post(theurl.clone())
        .json(&value)
        .send()
        .await;
        
    match resp {
        Ok(resp) => {
            let text = resp.text().await;
            match text {
                Ok(text_) => println!("Hub response {}", text_),
                Err(err) => println!("Failed to get resp {} ", err),
            }
        }
        Err(err) => println!("Failed to inform {} {}", theurl, err),
    };
    
    Ok(warp::reply::with_status("ok", http::StatusCode::OK))
}