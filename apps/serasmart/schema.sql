CREATE TABLE temperature (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  value REAL NOT NULL,
  reference_value NOT NULL    /* The value returned by a reliable source e.g external API */
);

CREATE TABLE humidity (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  value REAL NOT NULL
);

CREATE TABLE luminosity (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  value REAL NOT NULL
);

CREATE TABLE motion (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  area INTEGER NOT NULL,
  duration INTEGER NOT NULL,
  value REAL NOT NULL       /*  A value which indicates the magnitude of the motion/ or just 0 and 1 for true or false*/
);

CREATE TABLE events (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  event_location STRING NOT NULL,   /*  Could be one of the values: WINDOW, DOOR*/
  state REAL NOT NULL               /* 0 indicates closed, 1 indicates open, other has a custom meaning*/
);