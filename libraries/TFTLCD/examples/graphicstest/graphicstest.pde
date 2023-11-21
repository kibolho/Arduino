#define LCD_CS A3    
#define LCD_CD A2    
#define LCD_WR A1   
#define LCD_RD A0    
#define LCD_RESET A4
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF

#include "TFTLCD.h"
 TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void setup(void) {
  Serial.begin(9600);
  Serial.println("8 Bit LCD test!");
    tft.reset();
    uint16_t identifier = tft.readRegister(0x0);
  if (identifier == 0x9325) {
    Serial.println("Found ILI9325");
  } else if (identifier == 0x9328) {
    Serial.println("Found ILI9328");
  } else {
    Serial.print("Unknown driver chip ");
    Serial.println(identifier, HEX);
 //   while (1);
  }  
    tft.initDisplay();
}

void loop(void) {
  for (uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation); 
    delay(1000);
     tft.fillScreen(BLUE);
      delay(1000);
     tft.fillScreen(RED);
      delay(1000);
     tft.fillScreen(GREEN);
  }
}


