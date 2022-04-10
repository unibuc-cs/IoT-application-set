## Kodi2MQTT - Tested on Linux
Based on Kodi - media player center

1. Install Kodi - [link](https://kodi.tv/download/raspberry-pi).

`sudo apt-get install kodi`

2. Kodi2MQTT is an addon for Kodi. It can be installed via the addons menu - [tutorial](https://www.technadu.com/add-repository-to-kodi/189713/).

3. Launch an MQTT broker - mosquitto
```bash
# To install `mosquitto` run the following commands
git clone https://github.com/eclipse/mosquitto
cd mosquitto

```
4. Connect to MQTT topics supported by Kodi2MQTT [list here](https://github.com/owagner/kodi2mqtt#topics).

## Hue2MQTT - Tested on Linux

```bash
sudo apt install -y node npm
git clone https://github.com/hobbyquaker/hue2mqtt.js hue2mqtt
cd hue2mqtt
sudo npm install -g hue2mqtt
hue2mqtt -v debug -n hue -m localhost 
```
