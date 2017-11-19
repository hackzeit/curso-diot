#include "smartConfig.h"
#include "DHT.h"

const int dhtPin = D3;

DHT dht(dhtPin, DHTTYPE);

// sala.dht
Adafruit_MQTT_Subscribe dhtReq = Adafruit_MQTT_Subscribe(&mqtt, "sala/dht/req");
Adafruit_MQTT_Publish dhtSta = Adafruit_MQTT_Publish(&mqtt, "sala/dht/sta");

void dhtSetup(){
  dht.begin();
  dhtReq.setCallback(dhtCallback);
  mqtt.subscribe(&dhtReq);
}

void dhtCallback(char *payload, uint16_t len){
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer sensor DHT!");
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);
  dhtSta.publish(hic);
  //dhtSta.publish(hic,2);
}

