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
static WiFiClient wifi;
static Adafruit_MQTT_Client mqtt(&wifi, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_USER, MQTT_PASS);

void MQTT_connect();


/***************** Domotica ******************/

// Luz
void luzSetup();
void luzCallback(char *payload, uint16_t len);
void luzLeerToggle();
