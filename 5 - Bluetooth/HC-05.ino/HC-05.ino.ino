// Programa : Modulo BT HC-05 - Programacao
// Autor : Arduino e Cia

// Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h>
   
// Define os pinos para a serial   
SoftwareSerial MinhaSerial(6, 7); // RX, TX  
String command = "";   
   
void setup()   
{  
  // Inicia a serial  
  Serial.begin(115200);  
  // Mensagem inicial
  Serial.println("Digite os comandos AT :");  
  // Inicia a serial configurada nas portas 6 e 7
  MinhaSerial.begin(38400);  
}  
   
void loop()
{  
  // Verifica se ha comunicacao com o modulo
  // e efetua a leitura
  if (MinhaSerial.available()) 
  {  
     while(MinhaSerial.available()) 
     {
       command += (char)MinhaSerial.read();  
     }  
   Serial.println(command);  
   command = "";
  }  
  
  // Envio de comandos
  if (Serial.available())
  { 
    delay(10);
    MinhaSerial.write(Serial.read());  
  }  
}
