#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>


//Pinos usados no Ethernet Shield D4(apenas para o SD), D10, D11, D12, D13, alimentacao e o conector ICSP
//Pinos usados no LCD Shield A0 (Buttons), D4, D5, D6, D7, D8, D9, D10

int pinSensorPresenca = 3;
int pinLuz1 = 4;
int pinLuz2 = 5;
int pinLuz3 = 6;
int Buzzer = 7;

// MAC address for your Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


// Your Xively key to let you upload data
char xivelyKey[] = "sN6b22Im7SjOnBZpugcMyr639w8nY4EWwKpkvaGONoBfmu3f";
#define xivelyFeed 167023414
// Define the string for our datastream ID
char Luz1[] = "Luz1";
char Luz2[] = "Luz2";
char Luz3[] = "Luz3";
char SensorPresenca[] = "SensorPresenca";
char AlarmeTime[] = "Despertador";
char Alarme[] = "Alarme";

XivelyDatastream datastreams[] = {
  XivelyDatastream(Luz1, strlen(Luz1), DATASTREAM_FLOAT),
    XivelyDatastream(Luz2, strlen(Luz2), DATASTREAM_FLOAT),
      XivelyDatastream(Luz3, strlen(Luz3), DATASTREAM_FLOAT),
        XivelyDatastream(SensorPresenca, strlen(SensorPresenca), DATASTREAM_FLOAT),
         XivelyDatastream(AlarmeTime, strlen(AlarmeTime), DATASTREAM_FLOAT),
          XivelyDatastream(Alarme, strlen(Alarme), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(xivelyFeed, datastreams, 6 /* number of datastreams */);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pinLuz1, OUTPUT);
  pinMode(pinLuz2, OUTPUT);
  pinMode(pinLuz3, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(pinSensorPresenca, INPUT);

  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }
}

void loop() {

  int ret = xivelyclient.get(feed, xivelyKey);
  Serial.print("xivelyclient.get returned ");
  Serial.println(ret);

  if (ret > 0)
  {
    float x = feed[0].getFloat();
    Serial.println("Luz 1 - ");
    Serial.println(x);
    if(x>=1){
      digitalWrite(pinLuz1, HIGH);
    }else{
      digitalWrite(pinLuz1, LOW);
    }
    float y = feed[1].getFloat();
    Serial.println("Luz 2 - ");
    Serial.println(y);
    if(y>=1){
      digitalWrite(pinLuz2, HIGH);
    }else{
      digitalWrite(pinLuz2, LOW);
    }
    float z = feed[2].getFloat();
    Serial.println("Luz 3 - ");
    Serial.println(z);
    if(z>=1){
      Serial.println("Oi");
      digitalWrite(pinLuz3, HIGH);
    }else{
      digitalWrite(pinLuz3, LOW);
    }
     float w = feed[4].getFloat();
    Serial.println("Despertar - ");
    Serial.println(w);
    if(z>=1){
      Serial.println("Oi");
      digitalWrite(pinLuz3, HIGH);
    }else{
      digitalWrite(pinLuz3, LOW);
    }
  }

  datastreams[3].setFloat((float)digitalRead(pinSensorPresenca));

  Serial.println("Uploading it to Xively");
  int ret2 = xivelyclient.put(feed, xivelyKey);
  Serial.print("xivelyclient.put returned ");
  Serial.println(ret2);

  Serial.println();
  delay(1000);
}

void alarm(void){
  Serial.print("SOUND");  
  tone (Buzzer, 400);
  delay (500);
  tone (Buzzer, 1000);
  delay (500);
  noTone (Buzzer);
}

