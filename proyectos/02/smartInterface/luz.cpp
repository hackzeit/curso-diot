#include "smartInterface.h"

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
  pinMode(luzButton,INPUT);
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
    luzLedVal == luzOff;
  }
}

void luzLeerToggle(){
  if(digitalRead(luzButton) == LOW){
    luzSet.publish("toggle");

    // Espera a que se suelte el pulsador
    while(digitalRead(luzButton) == LOW);
  }
}
