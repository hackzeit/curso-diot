#include "smartConfig.h"

const int trigger = D6;
const int echo = D7;

// sala.pres
Adafruit_MQTT_Subscribe presReq = Adafruit_MQTT_Subscribe(&mqtt, "sala/pres/req");
Adafruit_MQTT_Publish presSta = Adafruit_MQTT_Publish(&mqtt, "sala/pres/sta");

void presenciaSetup(){
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  
  presReq.setCallback(presenciaCallback);
  mqtt.subscribe(&presReq);
}

void presenciaCallback(char *payload, uint16_t len){
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  long tiempo = (pulseIn(echo, HIGH)/2);
  float distancia = float(tiempo * 0.0343);
  
  Serial.println(distancia);

  presSta.publish(distancia);
}

