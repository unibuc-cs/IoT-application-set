- **Sensor** - continously relays information
- **Gadget** - actionable/toggleable; can receive commands and send status 

#### Gadget's MQTT API:
```
/update
        {"status":<int>} meaning depends on the gadget type; or something else
        - the gadget publishes its internal value
/set
        {"status":<int>}
/sync
        Triggers a resync
```
#### Sensor's MQTT API:
    {"value":<int>} or other format
