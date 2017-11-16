#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/********** WiFi Access Point ***********/
#define WLAN_SSID       "diot"
#define WLAN_PASS       "diot1234"

/********** MQTT Broker *****************/
#define MQTT_SERVER "m14.cloudmqtt.com"
#define MQTT_PORT   13600
#define MQTT_USER   "whyeaytn"
#define MQTT_PASS   "MjryhT6Dijp_"

/************ clientes wifi y mqtt*************/
extern WiFiClient wifi;
extern Adafruit_MQTT_Client mqtt;

void MQTT_connect();


/***************** Domotica ******************/

// Luz
void luzSetup();
void luzCallback(char *payload, uint16_t len);
void luzLeerToggle();
