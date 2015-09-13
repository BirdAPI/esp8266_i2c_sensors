#define SSID "ssid"
#define PASSWORD "password"
#define LOCATION "location"
#define BROKER_URL "192.168.1.100"
#define BROKER_PORT 1883
#define TOPIC "birdhome/api/temp/log"
#define SDA_PIN 0
#define SCL_PIN 2
#define BAUD_RATE 115200
#define DELAY_MS 5000

//#define _HDC1008 1
#define _MCP9808 1

String DEVICE_ID = "esp" + String(ESP.getChipId());

