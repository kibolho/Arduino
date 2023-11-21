/*
 ADS
 
 Circuit:
 SCP1000 sensor attached to pins 6, 7, 10 - 13:
 DRDY: pin 6
 CSB: pin 7
 MOSI: pin 11
 MISO: pin 12
 SCK: pin 13

 created 31 July 2010
 modified 14 August 2010
 by Abilio
 */

// the sensor communicates using SPI, so include the library:
#include <SPI.h>

const byte READ = 0b11111100;     // SCP1000's read command
const byte WRITE = 0b00000010;   // SCP1000's write command

// pins used for the connection with the sensor
// the other you need are controlled by the SPI library):
const int dataReadyPin = 6;
const int chipSelectPin = 7;

void setup() {
  Serial.begin(9600);

  // start the SPI library:
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  // initalize the  data ready and chip select pins:
  pinMode(dataReadyPin, INPUT);
  pinMode(chipSelectPin, OUTPUT);

  // writeRegister(endereço, valor, modo);
  writeRegister(0x00,0x00); // para as conversoes, DEVEMOS FAZER ISTO ANTES DE QQ COISA
  writeRegister(0x12,0x02); // desabilita o oscilador interno - isto deve ser feito antes de habilitar o oscilador externo
  writeRegister(0x01,0x0A); // Channel 1+ -> IN1     Channel 1- -> IN2
  writeRegister(0x02,0x1C); // Channel 2+ -> IN3     Channel 2- -> IN4
  writeRegister(0x03,0x00); // Disconecta o canal 3
  writeRegister(0x0A,0x0F); // Comum mode formado pelo IN1, IN2, IN3 e IN4
  writeRegister(0x0C,0x05); // Right-leg drive conectado no pino IN5 -- será o terra do sistema (meio da testa)
  // writeRegister(0x0D,0x00); //não há necessidade do Wilson amplifier
  // writeRegister(0x0E,0x00); //não há necessidade do Wilson amplifier
  // writeRegister(0x0F,0x00); //não há necessidade do Wilson amplifier
  // writeRegister(0x10,0x01); //não há necessidade do Wilson amplifier
  writeRegister(0x12,0x04); // habilita oscilador
  writeRegister(0x13,0x3F); // frequencia maxima de operação para todos os canais 
  //decimation R2 igual a 8 como default 
  writeRegister(0x22,0x10); // Configures the R3 decimation rate as 16 for channel 1.
  writeRegister(0x23,0x10); // Configures the R3 decimation rate as 16 for channel 2
  // writeRegister(0x24,0x10); // Set address 0x22 = 0x02: Configures the R3 decimation rate as 6 for channel 1
  writeRegister(0x27,0x08); // Configures the DRDYB source to channel 1 ECG (or fastest channel).
  writeRegister(0x2F,0x30); // Enables channel 1 and 2 for loop read-back mode.
  writeRegister(0x00,0x01); // Starts data conversion.

  
  // give the sensor time to set up:
  delay(100);
}

void loop() {
  //Select High Resolution Mode
  //writeRegister(0x03, 0x0A);

  // don't do anything until the data ready pin is high:
  if (digitalRead(dataReadyPin) == HIGH) {
    //Read the temperature data
    int Data = readRegister(0x50, 10);
    Serial.print("Data = ");
    Serial.print(Data);


//    //Read the pressure data highest 3 bits:
//    byte  pressure_data_high = readRegister(0x1F, 1);
//    pressure_data_high &= 0b00000111; //you only needs bits 2 to 0
//
//    //Read the pressure data lower 16 bits:
//    unsigned int pressure_data_low = readRegister(0x20, 2);
//    //combine the two parts into one 19-bit number:
//    long pressure = ((pressure_data_high << 16) | pressure_data_low) / 4;
//
//    // display the temperature:
//    Serial.println("\tPressure [Pa]=" + String(pressure));
  }
}

//Read from or write to register from the SCP1000:
unsigned int readRegister(byte thisRegister, int bytesToRead) {
  byte inByte = 0;           // incoming byte from the SPI
  unsigned int result = 0;   // result to return
  Serial.print(thisRegister, BIN);
  Serial.print("\t");
  // SCP1000 expects the register name in the upper 6 bits
  // of the byte. So shift the bits left by two bits:
  thisRegister = thisRegister << 2;
  // now combine the address and the command into one byte
  byte dataToSend = thisRegister & READ;
  Serial.println(thisRegister, BIN);
  // take the chip select low to select the device:
  digitalWrite(chipSelectPin, LOW);
  // send the device the register you want to read:
  SPI.transfer(dataToSend);
  // send a value of 0 to read the first byte returned:
  result = SPI.transfer(0x00);
  // decrement the number of bytes left to read:
  bytesToRead--;
  // if you still have another byte to read:
  if (bytesToRead > 0) {
    // shift the first byte left, then get the second byte:
    result = result << 8;
    inByte = SPI.transfer(0x00);
    // combine the byte you just got with the previous one:
    result = result | inByte;
    // decrement the number of bytes left to read:
    bytesToRead--;
  }
  // take the chip select high to de-select:
  digitalWrite(chipSelectPin, HIGH);
  // return the result:
  return (result);
}


//Sends a write command to SCP1000

void writeRegister(byte thisRegister, byte thisValue) {

  // SCP1000 expects the register address in the upper 6 bits
  // of the byte. So shift the bits left by two bits:
  thisRegister = thisRegister << 2;
  // now combine the register address and the command into one byte:
  byte dataToSend = thisRegister | WRITE;

  // take the chip select low to select the device:
  digitalWrite(chipSelectPin, LOW);

  SPI.transfer(dataToSend); //Send register location
  SPI.transfer(thisValue);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(chipSelectPin, HIGH);
}

