package main

import (
	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
	"soundsystem/handlers"
	"sync"
)

func main() {
	e := echo.New()

	//todo: handle the error!
	c, _ := handlers.NewContainer()

	// Middleware
	e.Use(middleware.CORS())
	e.Use(middleware.Logger())
	e.Use(middleware.Recover())

	// SongsGet -
	e.GET("/songs", c.SongsGet)

	// SongsIDelete -
	e.DELETE("/songs/:i", c.SongsIDelete)

	// SongsIGet -
	e.GET("/songs/:i", c.SongsIGet)

	// SongsPost -
	e.POST("/songs", c.SongsPost)

	// StatusGet -
	e.GET("/status", c.StatusGet)

	// StatusPost -
	e.POST("/status", c.StatusPost)

	// StorageGet -
	e.GET("/storage", c.StorageGet)

	// StorageIdDelete -
	e.DELETE("/storage/:id", c.StorageIdDelete)

	// StorageIdGet -
	e.GET("/storage/:id", c.StorageIdGet)

	// StorageIdPut -
	e.PUT("/storage/:id", c.StorageIdPut)

	// StoragePost -
	e.POST("/storage", c.StoragePost)

	wg := sync.WaitGroup{}

	wg.Add(1)
	go func() {
		defer wg.Done()

		c.BackgroundJob()
	}()

	// Start server
	wg.Add(1)
	go func() {
		defer wg.Done()

		e.Logger.Fatal(e.Start(":8080"))
	}()

	// Disabled for now
	// wg.Add(1)
	// go func() {
	// 	defer wg.Done()

	// 	c.InitMQTTClient("mqtt-server", 1883)
	// 	c.ConnectMQTTClient()
	// 	c.SubscribeToSongsQueue()
	// }()

	wg.Wait()
}
