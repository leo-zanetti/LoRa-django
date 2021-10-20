#include "heltec.h"
#define BAND 915E6

const unsigned long INTERVAL = 5000;
unsigned long lastSendTime = 0;

int i = 1;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  LoRa.receive();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastSendTime > INTERVAL) {
    // enviando a requisição do pacote ao slave
    Serial.print("Enviando requisição ao slave...");
    Serial.println(i);
    LoRa.beginPacket();
    LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print(i);
    LoRa.endPacket();
    lastSendTime = currentTime;
  }
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Recebido o pacote '");
    while (LoRa.available()) {
      String received = LoRa.readString();
      Serial.print(received);
      // print RSSI of packet
      Serial.print("' com RSSI igual a ");
      Serial.println(LoRa.packetRssi());
      if (received.charAt(0) == '1') {
        i = 2;
      } else if (received.charAt(0) == '2') {
        i = 1;
      }
    }
  }
}
