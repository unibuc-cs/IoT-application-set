use std::env::args;
use std::process;
use rand::{Rng, thread_rng};
use std::thread::sleep;
use std::time::Duration;
use paho_mqtt::{Client, PersistenceType};
use serde_json::json;

fn main() {
    let name = args().nth(1).unwrap_or("dust_0".to_string());
    let mut rng = thread_rng();

    let id: u16 = rng.gen();
    let cli = connect_mqtt(id);

    loop {
        let is_dust: bool = rng.gen();

        let content = json!({
            "name": name,
            "is_dust": is_dust,
        });
        publish_message(&cli, content.to_string().as_str(), "vacuum_cleaner_dust");
        sleep(Duration::from_secs(5));
    }
}

fn connect_mqtt(id: u16) -> Client {
    let mqtt_broker = args().nth(2).unwrap_or("tcp://broker.emqx.io:1883".to_string());
    let client_name = "dust_sensor".to_owned() + &id.to_string();

    let create_opts = paho_mqtt::CreateOptionsBuilder::new()
        .server_uri(mqtt_broker)
        .client_id(client_name)
        .persistence(PersistenceType::None)
        .finalize();

    // Create a client.
    let cli = paho_mqtt::Client::new(create_opts).unwrap_or_else(|err| {
        println!("Error creating the client: {:?}", err);
        process::exit(1);
    });

    let conn_opts = paho_mqtt::ConnectOptionsBuilder::new()
        .keep_alive_interval(Duration::from_secs(20))
        .clean_session(true)
        .finalize();

    // Connect and wait for it to complete or fail.
    if let Err(e) = cli.connect(conn_opts) {
        println!("Unable to connect:\n\t{:?}", e);
        process::exit(1);
    }

    return cli;
}

fn publish_message(cli: &Client, content: &str, topic: &str) {
    println!("Publishing messages on the {:?} topic: {:?}", topic, content);
    let msg = paho_mqtt::Message::new(topic, content.clone(), 0);
    let tok = cli.publish(msg);

    if let Err(e) = tok {
        println!("Error sending message: {:?}", e);
    }
}