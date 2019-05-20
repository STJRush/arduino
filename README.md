# arduino
For arduino code

The current project is to make some very low power sensors that can be placed around the community to measure things like soil moisture levels in green houses in Rush, weather data and perhalps some flooding data.

We would like to build a large network of very low power sensors in Rush using a technology called LoRa. These don't need WiFi and instead use radio to send data. The sensors can be small due to their low power. Each sensor will be a node and nodes will connect to a LoRa gateway (a Rpi on a network) to connect to the Things Network.


Update: 16/5/19:
-We've got a Raspberry Pi 3 recording weather data here:
https://thingspeak.com/channels/780882

This needs WiFi though and a lot of power so next step is to do this at much lower power with no WiFi near the sensors.


Update: 19/5/19:
-We've got a moisture sensor LoRa node sending data point to point to another node.
