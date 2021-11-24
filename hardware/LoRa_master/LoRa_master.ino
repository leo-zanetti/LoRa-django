#include "heltec.h"

#define BAND 915E6
#define NODES 2

const unsigned long INTERVAL = 5000;
const unsigned long TIMEOUT = 5000;

unsigned long lastSendTime = 0;
unsigned long timeoutFlag = 0;
unsigned long currentTime;

String received;

int i = 1;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/,
               true /*Heltec.LoRa Disable*/,
               true /*Serial Enable*/,
               true /*PABOOST Enable*/,
               BAND /*long BAND*/);
  LoRa.receive();
}

void loop() {
  currentTime = millis();
  if (i > NODES) {
    i = 1;
  }
  if (currentTime - lastSendTime > INTERVAL) {
    LoRa.beginPacket();
    LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print(i);
    LoRa.endPacket();
    lastSendTime = currentTime;
  }
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      received = LoRa.readString();
    }
    Serial.println(received + "/" + LoRa.packetRssi());
  } else if (currentTime - timeoutFlag > TIMEOUT) {
    i++;
    timeoutFlag = currentTime;
  }
}
