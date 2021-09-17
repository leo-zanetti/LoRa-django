#include "heltec.h"

#define BAND 915E6

long lastSendTime = 0;

String packet = "";
String id;
String temperature;
String humidity;

const int count = 0;
boolean check1;
boolean check2;
const String GETDATA = "get";
const String SETDATA = "set";

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Heltec.LoRa inicializado com sucesso!");
  Heltec.display->drawString(0, 20, "Eu sou o master!");
  Heltec.display->display();

  LoRa.crc();
  LoRa.receive();

  send();
}

void loop() {
  if (check1 == true && check2 == true) {
    send();
  } else {
    receive();
  }
}

void send() {
  //  Serial.println("Enviando request");
  //Inicializa o pacote
  LoRa.beginPacket();
  //Envia o que está contido em "GETDATA"
  LoRa.print(GETDATA);
  //Finaliza e envia o pacote
  LoRa.endPacket();
  check1 = false;
  check2 = false;
}

void receive() {
  //Tentamos ler o pacote
  int packetSize = LoRa.parsePacket();

  //Verificamos se o pacote tem o tamanho mínimo de caracteres que esperamos
  if (packetSize > SETDATA.length()) {
    String received = "";
    //Armazena os dados do pacote em uma string
    for (int i = 0; i < SETDATA.length(); i++) {
      received += (char) LoRa.read();
    }
    //Se o cabeçalho é o que esperamos
    if (received.equals(SETDATA)) {
      //Fazemos a leitura dos dados
      packet = LoRa.readString();
      //Mostramos os dados no display
      showData();
      if (packet.charAt(0) == '1') {
        Serial.println(packet);
        check1 = true;
      } else if (packet.charAt(0) == '2') {
        Serial.println(packet);
        check2 = true;
      }
    }
  }
}
void showData() {
  Heltec.display->clear();
  Heltec.display->drawString(0, 20, packet);
  Heltec.display->display();
}
