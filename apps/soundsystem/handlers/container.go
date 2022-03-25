package handlers

import (
	"fmt"
	mqtt "github.com/eclipse/paho.mqtt.golang"
	"soundsystem/models"
)

// Container will hold all dependencies for your application.
type Container struct {
	storedSongs           map[string]models.StoredSong
	playingQueue          []string
	status                string
	currentSecond         int
	sleepTimeMilliseconds int32
	shouldStop            bool
	mqttClient            mqtt.Client
}

func CreateClient(broker string, port int) mqtt.Client {
	var id = "soundsystem"
	opts := mqtt.NewClientOptions()
	opts.AddBroker(fmt.Sprintf("tcp://%s:%d", broker, port))
	opts.SetClientID(id)

	opts.SetDefaultPublishHandler(func(client mqtt.Client, message mqtt.Message) {
		fmt.Printf("Received message: %s from topic: %s which does not have a handler\n", message.Payload(), message.Topic())
	})

	opts.OnConnect = func(client mqtt.Client) {
		fmt.Printf("Client %s connected to %s:%d.", id, broker, port)
	}

	opts.OnConnectionLost = func(client mqtt.Client, err error) {
		fmt.Printf("MQTT connection lost: %v\n", err)
	}

	client := mqtt.NewClient(opts)

	return client
}

func (c *Container) InitMQTTClient(broker string, port int) {
	c.mqttClient = CreateClient(broker, port)
}

// NewContainer returns an empty or an initialized container for your handlers.
func NewContainer() (Container, error) {
	c := Container{
		storedSongs:           make(map[string]models.StoredSong),
		playingQueue:          make([]string, 0),
		status:                IdleStatus,
		currentSecond:         0,
		sleepTimeMilliseconds: 5000,
		shouldStop:            false,
		mqttClient:            nil,
	}
	return c, nil
}
