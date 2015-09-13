#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <Wire.h>
#include "config.h"

// HDC1008
#if defined(_HDC1008)
  #include <Adafruit_HDC1000.h>
  Adafruit_HDC1000 hdc = Adafruit_HDC1000();
  String SENSOR = "HDC1008";
#endif

// MCP9808
#if defined(_MCP9808)
  #include <Adafruit_MCP9808.h>
  Adafruit_MCP9808 mcp = Adafruit_MCP9808();
  String SENSOR = "MCP9808";
#endif

MQTT myMqtt(DEVICE_ID.c_str(), BROKER_URL, BROKER_PORT);

void myConnectedCb() {
  Serial.println("connected to MQTT server");
}

void myDisconnectedCb() {
  Serial.println("disconnected. try to reconnect...");
  delay(500);
  myMqtt.connect();
}

void myPublishedCb() {
  //Serial.println("published.");
}

void myDataCb(String& topic, String& data) {
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(data);
}

void setup() {
  Serial.begin(BAUD_RATE);
  delay(10);

  Wire.pins(SDA_PIN, SCL_PIN);

  Serial.println();
  Serial.println(DEVICE_ID);
  Serial.println();
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(SSID);
  
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

#if defined(_HDC1008)
  hdc.begin();
#elif defined(_MCP9808)
  mcp.begin();
#endif
  
  Serial.println("Connecting to MQTT server");  
  // setup callbacks
  myMqtt.onConnected(myConnectedCb);
  myMqtt.onDisconnected(myDisconnectedCb);
  myMqtt.onPublished(myPublishedCb);
  myMqtt.onData(myDataCb);
  Serial.println("connect mqtt...");
  myMqtt.connect();
  delay(10);
}

 
void loop() {
  delay(DELAY_MS);
  
#if defined(_HDC1008)
  float c = hdc.readTemperature();
  float f = c * 9.0 / 5.0 + 32.0;
  float h = hdc.readHumidity();
  Serial.println(String(c) + " C");
  Serial.println(String(f) + " F");
  Serial.println(String(h) + " % Humidity");
  if (h > 99.9){
    Serial.println("Error, invalid data...");
    return;
  }
#elif defined(_MCP9808)
  float c = mcp.readTempC();
  float f = c * 9.0 / 5.0 + 32.0;
  Serial.println(String(c) + " C");
  Serial.println(String(f) + " F");
  if (c > -0.07 && c < -0.05){
    Serial.println("Error, invalid data...");
    return;
  }
#endif
  
  String json = "{\"device_id\":\""+DEVICE_ID+"\",\"location\":\""+LOCATION+"\",\"sensor\":\""+SENSOR+"\",\"temp\":";
  json += f;
  json += ",\"unit\":\"F\",\"humidity\":";
#if defined(_HDC1008)
  json += h;
#else
  json += "null";
#endif
  json += "}";

  Serial.println(json);
 
  myMqtt.publish(TOPIC, json);
}
