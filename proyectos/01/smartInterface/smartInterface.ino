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

/************ clientes wifi y mqtt*************/
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_USER, MQTT_PASS);


/****************************** Feeds ***************************************/

// sala.luz
Adafruit_MQTT_Subscribe luzSta = Adafruit_MQTT_Subscribe(&mqtt, "sala/luz/sta");
Adafruit_MQTT_Publish luzSet = Adafruit_MQTT_Publish(&mqtt, "sala/luz/set");


/************* Funcionalidad de sala.luz **************/
const int luzOn = LOW;
const int luzOff = !luzOn;

int luzLed = LED_BUILTIN;
int luzLedVal = luzOn;

int luzButton = D2;

void luzSetup(){
  pinMode(luzLed,OUTPUT);
  pinMode(luzButton,INPUT_PULLUP);
  luzSta.setCallback(luzCallback);
  mqtt.subscribe(&luzSta);
}
void luzCallback(char *payload, uint16_t len) {
  String msg = String(payload);

  Serial.print("Luz: ");
  Serial.println(msg);

  if(msg == "on"){
    luzLedVal = luzOn;
  } else if(msg == "off"){
    luzLedVal = luzOff;
  }
  digitalWrite(luzLed,luzLedVal);
}
void luzLeerToggle(){
  int estado = digitalRead(luzButton);
  if(estado == LOW){
    luzSet.publish("toggle");

    // Espera a que se suelte el pulsador
    while(estado == LOW){
      estado = digitalRead(luzButton);
    }
  }
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
}

void loop() {
  MQTT_connect();
  mqtt.processPackets(2500);
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

  luzLeerToggle();
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
