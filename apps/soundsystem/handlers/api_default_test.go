package handlers

import (
	"github.com/labstack/echo/v4"
	"github.com/stretchr/testify/assert"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
)

var seed int64 = 42

type TestCase struct {
	path            string
	method          string
	reqBody         string
	expectedStatus  int
	expectedResBody string
	function        func(ctx echo.Context) error
	paramNames      []string
	paramValues     []string
}

func TestStorage(t *testing.T) {
	SeedPrng(seed)
	c, _ := NewContainer()

	tc := TestCase{
		path:            "/storage",
		method:          http.MethodPost,
		reqBody:         "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\"}",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\"}\n",
		function:        c.StoragePost,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "[{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\"}]\n",
		function:        c.StorageGet,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage/:id",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusNotFound,
		expectedResBody: "{\"message\":\"Song id not found in storage\"}\n",
		function:        c.StorageIdGet,
		paramNames:      []string{"id"},
		paramValues:     []string{"123"},
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage/:id",
		method:          http.MethodPut,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}\n",
		function:        c.StorageIdPut,
		paramNames:      []string{"id"},
		paramValues:     []string{"3440579354231278675"},
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage/:id",
		method:          http.MethodDelete,
		reqBody:         "",
		expectedStatus:  http.StatusNotImplemented,
		expectedResBody: "{\"message\":\"I'm too lazy\"}\n",
		function:        c.StorageIdDelete,
		paramNames:      []string{"id"},
		paramValues:     []string{"3440579354231278675"},
	}
	testRequest(t, tc)
}

func TestSongs(t *testing.T) {
	SeedPrng(seed)
	c, _ := NewContainer()

	tc := TestCase{
		path:            "/songs",
		method:          http.MethodPost,
		reqBody:         "{\"id\":\"3440579354231278675\"}",
		expectedStatus:  http.StatusNotFound,
		expectedResBody: "{\"message\":\"Song not found in storage\"}\n",
		function:        c.SongsPost,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage",
		method:          http.MethodPost,
		reqBody:         "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\"}",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\"}\n",
		function:        c.StoragePost,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs",
		method:          http.MethodPost,
		reqBody:         "{\"id\":\"3440579354231278675\"}",
		expectedStatus:  http.StatusNotFound,
		expectedResBody: "{\"message\":\"Song not found in storage\"}\n",
		function:        c.SongsPost,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage/:id",
		method:          http.MethodPut,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}\n",
		function:        c.StorageIdPut,
		paramNames:      []string{"id"},
		paramValues:     []string{"3440579354231278675"},
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs",
		method:          http.MethodPost,
		reqBody:         "{\"id\":\"3440579354231278675\"}",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}\n",
		function:        c.SongsPost,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "[{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}]\n",
		function:        c.SongsGet,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs/0",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}\n",
		function:        c.SongsIGet,
		paramNames:      []string{"i"},
		paramValues:     []string{"0"},
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs/0",
		method:          http.MethodDelete,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"message\":\"Deleted\"}\n",
		function:        c.SongsIDelete,
		paramNames:      []string{"i"},
		paramValues:     []string{"0"},
	}
	testRequest(t, tc)
}

func TestStatus(t *testing.T) {
	SeedPrng(seed)
	c, _ := NewContainer()

	c.InitMQTTClient("localhost", 9883)
	c.ConnectMQTTClient()
	c.SubscribeToSongsQueue()

	tc := TestCase{
		path:            "/status",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"status\":\"idle\",\"current_song\":{\"name\":\"\",\"format\":\"\"}}\n",
		function:        c.StatusGet,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage",
		method:          http.MethodPost,
		reqBody:         "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\"}",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\"}\n",
		function:        c.StoragePost,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/storage/:id",
		method:          http.MethodPut,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}\n",
		function:        c.StorageIdPut,
		paramNames:      []string{"id"},
		paramValues:     []string{"3440579354231278675"},
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/status",
		method:          http.MethodPut,
		reqBody:         "{\"status\":\"playing\"}",
		expectedStatus:  http.StatusBadRequest,
		expectedResBody: "{\"message\":\"Can't start playing, the queue is empty\"}\n",
		function:        c.StatusPost,
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs",
		method:          http.MethodPost,
		reqBody:         "{\"id\":\"3440579354231278675\"}",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}\n",
		function:        c.SongsPost,
	}
	testRequest(t, tc)

	c.SetSleepTime(300)
	c.PlaySong()

	tc = TestCase{
		path:            "/status",
		method:          http.MethodPut,
		reqBody:         "{\"status\":\"playing\"}",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"status\":\"playing\",\"current_song\":{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005}}\n",
		function:        c.StatusPost,
	}
	testRequest(t, tc)

	c.PlaySong()
	c.PlaySong()
	c.PlaySong()

	tc = TestCase{
		path:            "/status",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"status\":\"playing\",\"current_song\":{\"name\":\"The house of the Rising Sun\",\"format\":\"mp3\",\"id\":\"3440579354231278675\",\"length\":69,\"size\":6.60005},\"current_second\":3}\n",
		function:        c.StatusGet,
	}
	testRequest(t, tc)

	for i := 0; i < 400; i++ {
		c.PlaySong()
	}

	tc = TestCase{
		path:            "/status",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusOK,
		expectedResBody: "{\"status\":\"idle\",\"current_song\":{\"name\":\"\",\"format\":\"\"}}\n",
		function:        c.StatusGet,
	}
	testRequest(t, tc)

	c.mqttClient.Publish("soundsystem.songs.queue", 0, false, "invalid")
	c.mqttClient.Publish("soundsystem.songs.queue", 0, false, "{\"id\":\"not found\"}")
	c.mqttClient.Publish("soundsystem.songs.queue", 0, false, "{\"id\":\"3440579354231278675\"}")
}

func TestOthers(t *testing.T) {
	SeedPrng(seed)
	c, _ := NewContainer()

	tc := TestCase{
		path:            "/songs/123",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusNotFound,
		expectedResBody: "{\"message\":\"Song index not found\"}\n",
		function:        c.SongsIGet,
		paramNames:      []string{"i"},
		paramValues:     []string{"123"},
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs/abc",
		method:          http.MethodGet,
		reqBody:         "",
		expectedStatus:  http.StatusBadRequest,
		expectedResBody: "{\"message\":\"Index must be an integer\"}\n",
		function:        c.SongsIGet,
		paramNames:      []string{"i"},
		paramValues:     []string{"abc"},
	}
	testRequest(t, tc)

	tc = TestCase{
		path:            "/songs",
		method:          http.MethodPost,
		reqBody:         "wrong",
		expectedStatus:  http.StatusBadRequest,
		expectedResBody: "{\"message\":\"Invalid body format\"}\n",
		function:        c.SongsPost,
	}
	testRequest(t, tc)
}

func testRequest(t *testing.T, testCase TestCase) {
	e := echo.New()
	req := httptest.NewRequest(testCase.method, testCase.path, strings.NewReader(testCase.reqBody))
	req.Header.Set(echo.HeaderContentType, echo.MIMEApplicationJSON)

	rec := httptest.NewRecorder()
	ctx := e.NewContext(req, rec)

	ctx.SetPath(testCase.path)
	if testCase.paramNames != nil && testCase.paramValues != nil {
		ctx.SetParamNames(testCase.paramNames...)
		ctx.SetParamValues(testCase.paramValues...)
	}

	if assert.NoError(t, testCase.function(ctx)) {
		assert.Equal(t, testCase.expectedStatus, rec.Code)
		assert.Equal(t, testCase.expectedResBody, rec.Body.String())
	}
}
