/*
*  Projeto: Automação de Ar condicionado, utilizando sensor eletrônico de Temperatura LM35 e um Emissor de Infra-Vermelho.
*      Garante que Ar condicionado retorne ligar após uma queda de força elétrica, através do controle de Temperatura do ambiente.
*
* Bibliotecas utilizadas: 1)para envio do código RAW: IRemote encontrada no site: https://github.com/shirriff/Arduino-IRremote 
*       2)para leitura do sinal: Fora utilizado o Algoritmo encontrado no site abaixo:
*       http://www.analysir.com/blog/wp-content/uploads/2014/03/Arduino_Record_Long_AirConditioner_Infrared_Signals_10.txt
*
*
* Autor: Deividson Calixto da Silva email: deividsoncs@gmail.com
*/

#include <IRremote.h>
IRsend irsend;
//Desligar
unsigned int S_off[347]={9048, 4504, 592, 532, 568, 552, 564, 576, 568, 1656, 568, 1684, 588, 528, 572, 552, 564, 576, 544, 1684, 564, 576, 580, 1664, 568, 1704, 544, 576, 544, 1680, 568, 556, 588, 528, 568, 576, 568, 552, 544, 552, 564, 556, 564, 556, 564, 576, 568, 548, 564, 552, 576, 544, 568, 576, 544, 572, 544, 556, 564, 576, 544, 556, 564, 576, 544, 576, 544, 1676, 572, 572, 596, 520, 592, 552, 544, 552, 588, 1660, 568, 576, 544, 576, 544, 576, 564, 552, 544, 552, 592, 552, 568, 552, 544, 552, 592, 544, 568, 576, 544, 576, 568, 1680, 568, 1656, 592, 552, 568, 552, 568, 1680, 572, 1676, 572, 548, 596, 13476, 9040, 4480, 600, 548, 596, 516, 596, 528, 588, 1656, 596, 1676, 572, 548, 572, 548, 572, 548, 568, 1660, 592, 524, 592, 1656, 596, 1656, 592, 548, 596, 1648, 596, 548, 568, 528, 592, 552, 568, 548, 572, 524, 592, 552, 568, 552, 568, 552, 544, 552, 592, 548, 572, 548, 596, 520, 588, 552, 568, 528, 592, 528, 592, 552, 568, 552, 564, 528, 592, 1680, 548, 572, 544, 552, 592, 552, 568, 528, 592, 1676, 588, 532, 564, 576, 544, 576, 548, 548, 568, 552, 588, 556, 540, 576, 544, 552, 568, 552, 592, 552, 544, 572, 572, 1672, 592, 1656, 596, 548, 544, 576, 568, 1660, 592, 1656, 592, 552, 568, 13460, 9068, 4480, 596, 548, 572, 552, 568, 548, 572, 1676, 572, 1652, 596, 552, 568, 548, 572, 548, 568, 1656, 592, 528, 620, 1648, 596, 1648, 600, 524, 596, 1676, 572, 548, 572, 524, 592, 548, 572, 552, 568, 528, 592, 524, 596, 548, 568, 528, 620, 540, 572, 548, 568, 552, 568, 528, 592, 524, 596, 548, 572, 548, 572, 524, 592, 528, 592, 552, 568, 1680, 568, 524, 624, 540, 572, 548, 568, 528, 592, 1680, 568, 552, 568, 528, 592, 528, 592, 524, 596, 548, 572, 520, 600, 548, 568, 552, 596, 540, 568, 524, 596, 548, 572, 1652, 596, 1656, 596, 548, 568, 552, 568, 1680, 568, 1680, 572, 524, 620,};
//Padrao sinal RAW Ligar Ar Condicionado Consul 25oC
unsigned int S_pwr25[347]={9012, 4508, 564, 556, 592, 544, 568, 552, 564, 1684, 564, 1688, 564, 576, 544, 572, 544, 556, 564, 1684, 564, 576, 544, 1684, 568, 1684, 564, 576, 568, 1696, 544, 556, 568, 1680, 564, 576, 544, 556, 564, 576, 544, 576, 544, 576, 544, 576, 540, 580, 540, 580, 540, 556, 592, 564, 544, 576, 544, 576, 544, 576, 544, 552, 568, 576, 540, 580, 540, 1684, 568, 552, 568, 572, 544, 576, 544, 556, 588, 1696, 548, 552, 564, 580, 540, 576, 544, 576, 544, 576, 544, 576, 544, 576, 540, 556, 564, 576, 544, 576, 544, 556, 588, 1680, 560, 1688, 564, 576, 540, 556, 564, 1708, 544, 1684, 564, 1684, 564, 13516, 9036, 4508, 568, 556, 564, 576, 544, 576, 544, 1680, 568, 1684, 564, 576, 544, 576, 544, 576, 544, 1704, 544, 576, 568, 1676, 564, 1684, 568, 552, 568, 1680, 568, 556, 564, 1704, 544, 576, 544, 576, 544, 552, 568, 572, 544, 552, 568, 556, 592, 564, 544, 556, 564, 552, 568, 576, 544, 552, 568, 576, 544, 572, 548, 552, 564, 576, 544, 576, 544, 1684, 564, 556, 592, 544, 564, 576, 544, 576, 548, 1676, 568, 556, 564, 556, 564, 576, 544, 576, 544, 552, 564, 576, 544, 576, 544, 556, 588, 544, 568, 576, 544, 552, 568, 1684, 564, 1680, 568, 556, 564, 576, 544, 1704, 544, 1684, 568, 1680, 596, 13476, 9016, 4508, 568, 576, 568, 544, 568, 576, 540, 1684, 568, 1704, 544, 576, 544, 576, 544, 552, 564, 1708, 544, 556, 564, 1680, 568, 1680, 568, 576, 568, 1676, 568, 576, 540, 1684, 568, 576, 544, 576, 544, 552, 564, 556, 564, 552, 568, 552, 568, 572, 548, 576, 540, 576, 572, 544, 568, 552, 568, 552, 564, 576, 544, 552, 568, 576, 540, 576, 544, 1684, 568, 552, 564, 580, 540, 576, 544, 576, 572, 1676, 564, 576, 544, 552, 568, 572, 544, 576, 544, 576, 544, 576, 544, 576, 544, 576, 540, 576, 544, 556, 564, 576, 568, 1676, 568, 1704, 544, 576, 544, 556, 564, 1684, 564, 1684, 564, 1684, 564,};
//Padrao sinal RAW Ligar Ar Condicionado Consul 18oC
unsigned int S_pwr18[347]={9012, 4508, 568, 552, 592, 568, 544, 552, 568, 1684, 564, 1684, 564, 552, 568, 556, 564, 552, 568, 552, 568, 552, 564, 556, 564, 556, 564, 556, 588, 548, 564, 556, 564, 1684, 564, 556, 564, 556, 564, 552, 568, 552, 564, 552, 568, 556, 564, 556, 564, 552, 568, 552, 592, 544, 568, 576, 544, 552, 564, 556, 564, 552, 568, 556, 564, 576, 544, 1680, 568, 552, 568, 576, 544, 552, 568, 572, 572, 1672, 568, 552, 568, 576, 544, 552, 568, 552, 564, 556, 564, 576, 544, 552, 568, 552, 568, 572, 544, 552, 568, 1684, 592, 544, 568, 552, 568, 1684, 564, 1680, 568, 1684, 564, 552, 568, 1684, 564, 13508, 9048, 4504, 568, 556, 564, 556, 564, 552, 568, 1680, 568, 1684, 564, 556, 564, 552, 568, 552, 568, 552, 568, 552, 592, 568, 544, 552, 568, 552, 564, 556, 564, 556, 564, 1680, 568, 576, 544, 576, 544, 552, 568, 552, 568, 576, 540, 556, 592, 544, 568, 552, 564, 556, 564, 552, 568, 552, 568, 552, 568, 552, 564, 556, 564, 556, 564, 576, 544, 1684, 564, 552, 596, 544, 564, 552, 568, 556, 564, 1684, 564, 556, 564, 552, 568, 556, 564, 576, 544, 552, 568, 552, 564, 576, 544, 552, 592, 568, 544, 556, 564, 1684, 564, 552, 568, 556, 564, 1680, 568, 1684, 564, 1684, 564, 556, 564, 1680, 596, 13504, 8992, 4504, 568, 556, 592, 544, 564, 556, 564, 1684, 564, 1684, 568, 552, 568, 552, 564, 556, 564, 556, 564, 552, 568, 552, 568, 552, 564, 556, 592, 544, 568, 552, 564, 1684, 568, 552, 568, 552, 564, 556, 564, 556, 564, 552, 568, 552, 564, 556, 568, 572, 544, 556, 592, 540, 568, 556, 564, 556, 564, 556, 564, 552, 568, 552, 564, 556, 564, 1684, 568, 552, 564, 556, 564, 552, 568, 556, 588, 1676, 568, 552, 564, 556, 564, 556, 564, 552, 568, 552, 568, 552, 568, 552, 564, 556, 564, 576, 544, 576, 544, 1680, 596, 544, 564, 556, 564, 1684, 568, 1680, 568, 1684, 564, 556, 564, 1684, 564,};
int enviou = 0;

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  Blynk using a LED widget on your phone!

  App project setup:
    LED widget on V1

  WARNING :
  For this example you'll need SimpleTimer library:
    https://github.com/jfturcot/SimpleTimer
  Visit this page for more information:
    http://playground.arduino.cc/Code/SimpleTimer
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <SimpleTimer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "4da29596283245ba81ce2ac5632176dc";

#define W5100_CS  10
#define SDCARD_CS 4

WidgetLED led1(V1);

SimpleTimer timer;

// V1 LED Widget is blinking
void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
    irsend.sendRaw(S_off, 347, 38);
  } else {
    led1.on();
    Serial.println("LED on V1: on");
    irsend.sendRaw(S_pwr18, 347, 38);
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  Blynk.begin(auth);
  // You can also specify server:
  //Blynk.begin(auth, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8442);

  timer.setInterval(1000L, blinkLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}



void loop() {
ligarAr();
delay(1000);

}

void ligarAr(){
    Serial.println("Ligando...");
    irsend.sendRaw(S_pwr18, 347, 38);
    Serial.println("Executando a 38 Hz");
    delay(10000);
    Serial.println("Desligando...");
    irsend.sendRaw(S_off, 347, 38);
    Serial.println("Executando a 38 Hz");
     delay(10000);
}
