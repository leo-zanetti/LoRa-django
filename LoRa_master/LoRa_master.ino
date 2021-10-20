#include "heltec.h"
#define BAND 915E6
#define INTERVAL 5000

int i = 1;
int j = 2;
long lastSendTime = 0;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  LoRa.receive();
}

void loop() {
  delay(INTERVAL);
  // enviando a requisição do pacote ao slave
  Serial.print("Enviando requisição ao slave...");
  Serial.println(i);
  LoRa.beginPacket();
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(i);
  LoRa.endPacket();
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Recebido o pacote '");
    while (LoRa.available()) {
      String received = LoRa.readString();
      Serial.print(received);
    }
    // print RSSI of packet
    Serial.print("' com RSSI igual a ");
    Serial.println(LoRa.packetRssi());
  }
  
  delay(INTERVAL);
  
  // enviando a requisição do pacote ao slave
  Serial.print("Enviando requisição ao slave...");
  Serial.println(j);
  LoRa.beginPacket();
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(j);
  LoRa.endPacket();

  packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Recebido o pacote '");
    while (LoRa.available()) {
      String received = LoRa.readString();
      Serial.print(received);
    }
    // print RSSI of packet
    Serial.print("' com RSSI igual a ");
    Serial.println(LoRa.packetRssi());
  }
}
