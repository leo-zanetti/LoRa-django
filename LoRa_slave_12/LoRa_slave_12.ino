#include "heltec.h"

#define BAND 915E6

int sensorPin = 13;

const String GETDATA = "get";
const String SETDATA = "set";

String packet = "";
int id = 2;
float moisture;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();

  Heltec.display->drawString(0, 0, "Heltec.LoRa inicializado!");
  Heltec.display->drawString(0, 20, "Eu sou o slave 12!");
  Heltec.display->display();
  delay(1000);

  Serial.println("LoRa iniciado para o slave 12");

  LoRa.crc();
  LoRa.receive();
}

void loop() {
  //Tenta ler o pacote
  int packetSize = LoRa.parsePacket();

  //Verifica se o pacote possui a quantidade de caracteres que esperamos
  if (packetSize == GETDATA.length())
  {
    String received = "";

    //Armazena os dados do pacote em uma string
    while (LoRa.available())
    {
      received += (char) LoRa.read();
    }
    Serial.println(received);
    if (received.equals(GETDATA))
    {
      //Faz a leitura dos dados
      readData();
      Serial.println("Criando pacote para envio");
      //Cria o pacote para envio
      LoRa.beginPacket();
      LoRa.print(SETDATA);
      LoRa.print(packet);
      //Finaliza e envia o pacote
      LoRa.endPacket();
      showSentData();
    }
  }
}

void readData()
{
  moisture = (100 - ((analogRead(sensorPin) / 1023.00) * 100));
  packet = String(id) + "/" + String(moisture);
}

void showSentData()
{
  //Mostra no display
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Nó:" + String(id));
  Heltec.display->drawString(0, 10, "Enviou:");
  Heltec.display->drawString(0, 20, String(moisture));
  Heltec.display->display();
  Serial.print("Enviou:");
  Serial.println(packet);
}