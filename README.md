# ESP8266 i2c Sensors #

Various sensor modules to work with BirdHome and other IoT platforms using the ESP8266 module.

## Dependencies ##
- Arduino Board Support for ESP8266 [https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino)
- MQTT client library for ESP8266 [https://github.com/tuanpmt/esp_mqtt](https://github.com/tuanpmt/esp_mqtt)

### Optional Sensor Libraries (Download the one for your i2c sensor) ###
- Adafruit HDC1000 Library [https://github.com/adafruit/Adafruit_HDC1000_Library](https://github.com/adafruit/Adafruit_HDC1000_Library)
- Adafruit MCP9808 Library [https://github.com/adafruit/Adafruit_MCP9808_Library](https://github.com/adafruit/Adafruit_MCP9808_Library)

## Supported Sensors ##
- Adafruit HDC1008 [http://www.adafruit.com/product/2635](http://www.adafruit.com/product/2635)
- Adafruit MCP9808 [http://www.adafruit.com/product/1782](http://www.adafruit.com/product/1782)

## Install ##
- Rename `config-template.h` to `config.h`
- Open the `*.ino` file with the Arduino IDE
- Change the values in `config.h` to match your values
- Verify your correct model of ESP8266 board is selected in the `Tools->Board` menu in the Arduino IDE
- Verify the correct port is selected in the `Tools->Port` menu in the Arduino IDE
- Compile the program and flash to the ESP8266 module