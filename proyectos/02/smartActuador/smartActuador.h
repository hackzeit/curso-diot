#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/********** WiFi Access Point ***********/
#define WLAN_SSID       "network"
#define WLAN_PASS       "password"

/********** MQTT Broker *****************/
#define MQTT_SERVER "m14.cloudmqtt.com"
#define MQTT_PORT   1883
#define MQTT_USER   "user"
#define MQTT_PASS   "key" 

/************ clientes wifi y mqtt*************/
extern WiFiClient wifi;
extern Adafruit_MQTT_Client mqtt;

void MQTT_connect();

/*************** Actuadores *******************/

void luzSetup();
void luzCallback(char *payload, uint16_t len);
