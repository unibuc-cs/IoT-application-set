package models

type StoredSong struct {

	Name string `json:"name"`

	Format string `json:"format"`

	Id string `json:"id,omitempty"`

	Length int32 `json:"length,omitempty"`

	Size float32 `json:"size,omitempty"`
}
