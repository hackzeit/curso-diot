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
#define MQTT_PASS   "pass"

/********** DHT *****************/
#define DHTTYPE DHT11

/************ clientes wifi y mqtt*************/
extern WiFiClient wifi;
extern Adafruit_MQTT_Client mqtt;

void wifiSetup();
void MQTT_connect();

/***************** Domotica ******************/

// DHT - Humedad y Temperatura
void dhtSetup();
void dhtCallback(char *payload, uint16_t len);



