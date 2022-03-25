package models

type Status struct {

	Status string `json:"status,omitempty"`

	CurrentSong QueuedSong `json:"current_song,omitempty"`

	CurrentSecond int32 `json:"current_second,omitempty"`
}
