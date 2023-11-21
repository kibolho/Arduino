// Programa : Teste teclado no Arduino USB Host Shield
// Alteracoes e adaptacoes : FILIPEFLOP
// Baseado no exemplo USBHIDBootKbd da biblioteca USB_Host_Shield_2.0
 
#include <hidboot.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif
 
class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);
 
  protected:
    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};
 
void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
};
 
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii(mod, key);
  if (c)
    OnKeyPressed(c);
}
 
void KbdRptParser::OnKeyPressed(uint8_t key)
{
  // Se a tecla ENTER foi pressionada, vai para a linha seguinte
  if(key == 19)
  {
    Serial.println((char)key);
  }
  // Caso contrario, imprime na mesma linha
  else
  {
    Serial.print((char)key);
  }
};
 
USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
 
uint32_t next_time;
 
KbdRptParser Prs;
 
void setup()
{
  Serial.begin( 115200 );
  Serial.println("Utilize o teclado USB...");
 
  if (Usb.Init() == -1)
    Serial.println("USB Host Shield nao encontrado !");
  delay( 200 );
  next_time = millis() + 5000;
  HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
}
 
void loop()
{
  Usb.Task();
}
