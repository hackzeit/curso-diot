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
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_USER, MQTT_PASS);


/****************************** Feeds ***************************************/

// sala.luz
Adafruit_MQTT_Subscribe luzSet = Adafruit_MQTT_Subscribe(&mqtt, "sala/luz/set");
Adafruit_MQTT_Publish luzSta = Adafruit_MQTT_Publish(&mqtt, "sala/luz/sta");


/************* Funcionalidad de sala.luz **************/
int luzPin = LED_BUILTIN;
int luzVar = LOW;
const int luzOn = LOW;
const int luzOff = !luzOn;
void luzSetup(){
  pinMode(luzPin,OUTPUT);
}
void luzCallback(char *payload, uint16_t len) {
  String msg = String(payload);

  Serial.print("Luz peticion entrante: ");
  Serial.println(msg);
  Serial.print("Estado: ");
  Serial.print(luzVar == luzOn? "on":"off");
  Serial.print(" -> ");

  if(msg == "on"){
    luzVar = luzOn;
  } else if(msg == "off"){
    luzVar == luzOff;
  } else if(msg == "toggle"){
    luzVar = !luzVar;
  }

  String estado = (luzVar == luzOn? "on":"off");
  Serial.println(estado);

  luzSta.publish(estado.c_str());
}


void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Projecto 01: Smart Actuador con codigo modular"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // luz
  luzSetup();
  luzSet.setCallback(luzCallback);
  mqtt.subscribe(&luzSet);
}

void loop() {
  MQTT_connect();
  mqtt.processPackets(10000);
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
