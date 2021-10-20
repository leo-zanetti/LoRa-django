#include "heltec.h"

#define BAND 915E6

int sensorPin = 13;
String received;
String packet = "";
String request = "2";
int id = 2;
float moisture;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
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

void readData()
{
  moisture = (100 - ((analogRead(sensorPin) / 1023.00) * 100));
  packet = String(id) + "/" + String(moisture);
  Serial.print("Medidas empacotadas: ");
  Serial.println(packet);
}
