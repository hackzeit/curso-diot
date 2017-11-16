#include "smartActuador.h"

WiFiClient wifi;
Adafruit_MQTT_Client mqtt(&wifi, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_USER, MQTT_PASS);

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Projecto 02: Smart Actuador con codigo modular"));

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
  mqtt.processPackets(10000);
  if (! mqtt.ping()) {
    mqtt.disconnect();
  }
}
