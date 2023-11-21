 /*
 created 31 July 2010
 modified 14 August 2010
 by Tom Igoe
 ADS1293 sensor attached to pins 6, 7, 10 - 13:
 DRDY: pin 6
 CSB: pin 7
 MOSI: pin 11
 MISO: pin 12
 SCK: pin 13

 */

// the sensor communicates using SPI, so include the library:
#include <SPI.h>

#define Data_In 11 //MOSI - write data into ADS1293
#define Data_read 12 //MISO - read data into ADS1293
#define SPICLOCK 13 //sck
//#define SLAVESELECT 10 //ss -- Chip select bar

// ADS 1293 memory register addresses:

const int status = 0x30;

//Important write memory register addresses:
const int CH_CNFG = 0x2F;      // Configure Channel for Loop Read Back Mode address
const int CNFG = 0x00;      // Main Configuration resister address
// pins used for the connection with the sensor
// the other you need are controlled by the SPI library):
const int dataReadyPin = 6;
const int CSB  = 7;
void setup() {
  Serial.begin(9600);
  // start the SPI library:
  SPI.begin();
  //SPI.setBitOrder(MSBFIRST);
  //SPI.setDataMode(SPI_MODE2);// check the mode for the AFE
  //SPI.setClockDivider(SPI_CLOCK_DIV2);// this means 8MHz SCLK to the AFE
 
  // initalize the  data ready and chip select pins:
  pinMode(dataReadyPin , INPUT); // Data ready bar
  pinMode(CSB , OUTPUT);
 
  //pinMode(Data_In, OUTPUT);
  //pinMode(Data_read, INPUT);
  //pinMode(SPICLOCK, OUTPUT);
 
 // digitalWrite(CSB , LOW);
  //Configure ADS12993
   // Initiate SOC
  // Configure Channels
  writeRegister(CNFG , 0x00);
  writeRegister(0x27, 0x01);
  writeRegister(CH_CNFG , 0x32); // Enable Loop read back mode
  writeRegister(CNFG , 0x01);
 
   //digitalWrite(CSB , HIGH);
  // give the sensor time to set up:
 delay(1000); // Delay 1 sec
}

void loop() {

  // digitalWrite(CSB , LOW);
 
  delay(100);
 
  Serial.print(digitalRead(dataReadyPin));

  // don't do anything until the data ready pin is high:
  if (digitalRead(dataReadyPin) == HIGH) {
    int Status_read = readRegister(status , 1);
    Serial.print("Status_read :");
    Serial.println(Status_read);
    //Read the temperature data
    int ECGData1_Ch1 = readRegister(0x3A , 3);
    
    Serial.print("ECG Channels  = ");
    Serial.println(ECGData1_Ch1);
  }
  delay(1000);
  /* if (digitalRead(dataReadyPin) == HIGH) {
    delay(100);
  }
  digitalWrite(chipSelectPin, HIGH); 
  // digitalWrite(CSB , HIGH);*/
}

unsigned int readRegister(byte thisRegister, int bytesToRead ) {
  byte inByte = 0;           // incoming byte from the SPI
  unsigned int result = 0;   // result to return
  //Serial.print(thisRegister, HEX);
  //Serial.println("\t");

  // take the chip select low to select the device:
  digitalWrite(CSB, LOW);
  // send the device the register you want to read:
  SPI.transfer(thisRegister);
  // send a value of 0 to read the first byte returned:
  result = SPI.transfer(0x00);
  // decrement the number of bytes left to read:
  bytesToRead--;
 
  // if you still have another byte to read:
  if (bytesToRead > 0) {
    thisRegister++;
    SPI.transfer(thisRegister);
    // shift the first byte left, then get the second byte:
    result = result << 8;
    inByte = SPI.transfer(0x00);
    // combine the byte you just got with the previous one:
    result = result | inByte;
    // decrement the number of bytes left to read:
    bytesToRead--;
  }
  // take the chip select high to de-select:
  digitalWrite(CSB, HIGH);
  // return the result:
  return(result);
}
void writeRegister(byte thisRegister, byte thisValue) {

  // take the chip select low to select the device:
  digitalWrite(CSB, LOW);

  SPI.transfer(thisRegister); //Send register location
  SPI.transfer(thisValue);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(CSB, HIGH);
}

