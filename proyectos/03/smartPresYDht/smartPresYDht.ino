#include "smartConfig.h"

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Projecto 03: Smart sensor de temperatura"));

  wifiSetup();
  dhtSetup();
  presenciaSetup(); // inicializa el dht y configura la subscricion a mqtt
}

void loop() {
  MQTT_connect();
  mqtt.processPackets(10000);
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}
