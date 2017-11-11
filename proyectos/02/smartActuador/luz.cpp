#include "Arduino.h"
#include "smartActuador.h"

/****************** Feeds *********************/
// sala.luz
Adafruit_MQTT_Subscribe luzSet = Adafruit_MQTT_Subscribe(&mqtt, "sala/luz/set");
Adafruit_MQTT_Publish luzSta = Adafruit_MQTT_Publish(&mqtt, "sala/luz/sta");


const int luzOn = LOW;
const int luzOff = !luzOn;

int luzPin = LED_BUILTIN;
int luzVar = LOW;


void luzSetup(){
  pinMode(luzPin,OUTPUT);
  luzSet.setCallback(luzCallback);
  mqtt.subscribe(&luzSet);
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
