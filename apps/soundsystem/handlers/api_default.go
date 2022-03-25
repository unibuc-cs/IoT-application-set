package handlers

import (
	"encoding/json"
	"errors"
	"fmt"
	mqtt "github.com/eclipse/paho.mqtt.golang"
	"github.com/labstack/echo/v4"
	"math/rand"
	"net/http"
	"soundsystem/models"
	"strconv"
	"time"
)

const IdleStatus = "idle"
const PlayingStatus = "playing"
const PausedStatus = "paused"

func (c *Container) SetSleepTime(milliseconds int32) {
	c.sleepTimeMilliseconds = milliseconds
}

func SeedPrng(seed int64) {
	rand.Seed(seed)
}

func (c *Container) BackgroundJob() {
	for !c.shouldStop {
		time.Sleep(time.Duration(c.sleepTimeMilliseconds) * time.Millisecond)
		c.PlaySong()
	}
}

func (c *Container) PlaySong() {
	if c.status != PlayingStatus {
		return
	}

	if len(c.playingQueue) == 0 {
		c.status = IdleStatus
		c.currentSecond = 0
		c.PublishStatus()
		return
	}

	x := int(c.sleepTimeMilliseconds) / int(time.Millisecond)
	if x == 0 {
		x = 1
	}
	c.currentSecond += x
	if c.currentSecond >= int(c.storedSongs[c.playingQueue[0]].Length) {
		fmt.Println("Song finished ", c.storedSongs[c.playingQueue[0]].Name)
		c.playingQueue = c.playingQueue[1:]
		c.currentSecond = 0
	} else {
		fmt.Printf("%d/%d song %s\n", c.currentSecond, int(c.storedSongs[c.playingQueue[0]].Length),
			c.storedSongs[c.playingQueue[0]].Name)
	}
	c.PublishStatus()
}

// SongsGet -
func (c *Container) SongsGet(ctx echo.Context) error {
	songs := make([]models.StoredSong, len(c.playingQueue))
	for i, id := range c.playingQueue {
		songs[i] = c.storedSongs[id]
	}

	return ctx.JSON(http.StatusOK, songs)
}

// SongsIDelete -
func (c *Container) SongsIDelete(ctx echo.Context) error {
	i, err := getIndexParam(ctx, c.playingQueue)
	if err != nil {
		return nil
	}

	c.playingQueue = append(c.playingQueue[:i], c.playingQueue[i+1:]...)
	return ctx.JSON(http.StatusOK, models.Message{
		Message: "Deleted",
	})
}

// SongsIGet -
func (c *Container) SongsIGet(ctx echo.Context) error {
	i, err := getIndexParam(ctx, c.playingQueue)
	if err != nil {
		return nil
	}

	return ctx.JSON(http.StatusOK, c.storedSongs[c.playingQueue[i]])
}

// SongsPost -
func (c *Container) SongsPost(ctx echo.Context) error {
	obj := new(models.SongRequest)
	err := getReqBodyInto(ctx, obj)
	if err != nil {
		return nil
	}

	song, exists := c.storedSongs[obj.Id]
	if !exists || song.Size == 0 {
		return ctx.JSON(http.StatusNotFound, models.Message{
			Message: "Song not found in storage",
		})
	}

	c.playingQueue = append(c.playingQueue, song.Id)
	qsong := models.QueuedSong{
		Name:   song.Name,
		Format: song.Format,
		Id:     song.Id,
		Length: song.Length,
		Size:   song.Size,
		Index:  int32(len(c.playingQueue) - 1),
	}

	return ctx.JSON(http.StatusOK, qsong)
}

func (c *Container) createStatusStruct() models.Status {
	var qsong models.QueuedSong
	if len(c.playingQueue) > 0 {
		song := c.storedSongs[c.playingQueue[0]]
		qsong = models.QueuedSong{
			Name:   song.Name,
			Format: song.Format,
			Id:     song.Id,
			Length: song.Length,
			Size:   song.Size,
			Index:  int32(len(c.playingQueue) - 1),
		}
	}

	return models.Status{
		Status:        c.status,
		CurrentSecond: int32(c.currentSecond),
		CurrentSong:   qsong,
	}
}

// StatusGet -
func (c *Container) StatusGet(ctx echo.Context) error {
	return ctx.JSON(http.StatusOK, c.createStatusStruct())
}

// StatusPost -
func (c *Container) StatusPost(ctx echo.Context) error {
	obj := new(models.InlineObject1)
	err := getReqBodyInto(ctx, obj)
	if err != nil {
		return nil
	}

	if obj.Status == PlayingStatus && len(c.playingQueue) == 0 {
		return ctx.JSON(http.StatusBadRequest, models.Message{
			Message: "Can't start playing, the queue is empty",
		})
	}

	c.status = obj.Status

	if obj.Status == IdleStatus {
		c.playingQueue = make([]string, 0)
		c.currentSecond = 0
	}

	c.PublishStatus()
	return c.StatusGet(ctx)
}

// StorageGet -
func (c *Container) StorageGet(ctx echo.Context) error {
	songs := make([]models.StoredSong, len(c.storedSongs))
	i := 0
	for _, v := range c.storedSongs {
		songs[i] = v
		i++
	}

	return ctx.JSON(http.StatusOK, songs)
}

// StorageIdDelete -
func (c *Container) StorageIdDelete(ctx echo.Context) error {
	return ctx.JSON(http.StatusNotImplemented, models.HelloWorld{
		Message: "I'm too lazy",
	})
}

// StorageIdGet -
func (c *Container) StorageIdGet(ctx echo.Context) error {
	id := ctx.Param("id")
	song, exists := c.storedSongs[id]
	if !exists {
		return ctx.JSON(http.StatusNotFound, models.Message{
			Message: "Song id not found in storage",
		})
	}

	return ctx.JSON(http.StatusOK, song)
}

// StorageIdPut -
func (c *Container) StorageIdPut(ctx echo.Context) error {
	id := ctx.Param("id")
	song, exists := c.storedSongs[id]
	if !exists {
		return ctx.JSON(http.StatusNotFound, models.Message{
			Message: "Song id not found in storage",
		})
	}

	// Fake implementation
	song.Size = rand.Float32() * 100
	song.Length = rand.Int31()%200 + 1
	c.storedSongs[id] = song

	return ctx.JSON(http.StatusOK, c.storedSongs[id])
}

// StoragePost -
func (c *Container) StoragePost(ctx echo.Context) error {
	obj := new(models.BaseSong)
	err := getReqBodyInto(ctx, obj)
	if err != nil {
		return nil
	}

	id := strconv.Itoa(rand.Int())
	c.storedSongs[id] = models.StoredSong{
		Name:   obj.Name,
		Format: obj.Format,
		Id:     id,
		Length: 0,
		Size:   0,
	}

	return ctx.JSON(http.StatusOK, c.storedSongs[id])
}

func (c *Container) ConnectMQTTClient() {
	if token := c.mqttClient.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}
}

func (c *Container) SubscribeToSongsQueue() {
	topic := "soundsystem.songs.queue"
	token := c.mqttClient.Subscribe(topic, 1, func(client mqtt.Client, message mqtt.Message) {
		sr := models.SongRequest{}
		err := json.Unmarshal(message.Payload(), &sr)
		if err != nil {
			fmt.Printf("Invalid message format for song request: %s\n", message.Payload())
			return
		}

		fmt.Printf("Received song request %s\n", sr.Id)

		song, exists := c.storedSongs[sr.Id]
		if !exists || song.Size == 0 {
			fmt.Printf("Requested song %s not found\n", sr.Id)
			return
		}

		c.playingQueue = append(c.playingQueue, song.Id)
		c.PublishStatus()
	})
	token.Wait()
	fmt.Printf("Subscribed to topic %s\n", topic)
}

func (c *Container) PublishStatus() {
	status := c.createStatusStruct()
	bytes, err := json.Marshal(status)
	if err != nil {
		fmt.Println("Could not publish status")
		return
	}

	if c.mqttClient == nil {
		fmt.Println("MQTT not connected, ignoring status publishing")
		return
	}

	c.mqttClient.Publish("soundsystem.status", 0, false, bytes)
}

func getIndexParam(ctx echo.Context, playingQueue []string) (int, error) {
	i, err0 := strconv.Atoi(ctx.Param("i"))

	if err0 != nil {
		err := ctx.JSON(http.StatusBadRequest, models.Message{
			Message: "Index must be an integer",
		})
		if err != nil {
			return 0, err
		}
		return 0, err0
	}

	if i >= len(playingQueue) {
		err := ctx.JSON(http.StatusNotFound, models.Message{
			Message: "Song index not found",
		})
		if err != nil {
			return 0, err
		}
		return 0, errors.New("not found")
	}

	return i, nil
}

func getReqBodyInto(ctx echo.Context, obj interface{}) error {
	err0 := ctx.Bind(obj)
	if err0 != nil {
		err := ctx.JSON(http.StatusBadRequest, models.Message{
			Message: "Invalid body format",
		})
		if err != nil {
			return err
		}
		return err0
	}

	return nil
}
