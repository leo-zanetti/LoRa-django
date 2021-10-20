#include "heltec.h"
#include <DHT.h>

#define BAND 915E6
#define DHTPIN 21
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

String received;
String packet = "";
String request = "1";
int id = 1;
float temperature;
float humidity;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  dht.begin();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      received = (char)LoRa.read();
      if (received.equals(request)) {
        Serial.print("Pacote recebido: ");
        Serial.println(received);
        readData();
        Serial.println("Enviando pacote...");
        LoRa.beginPacket();
        LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
        LoRa.print(packet);
        LoRa.endPacket();
      }
    }
  }
}

void readData() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  packet = String(id) + "/" + String(temperature) + "/" + String(humidity);
  Serial.print("Medidas empacotadas: ");
  Serial.println(packet);
}
