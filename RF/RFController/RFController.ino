#include <VirtualWire.h>
#include <math.h> 
//PressJoystick Button 1 Button 2
int buttons[3]={10, 11, 12};

#define AxisX A1
#define AxisY A0
#define RFData 3

int x = 0;
char xCharMsg[4];
int y = 0;
char yCharMsg[4];

char str[255] = {0};
char sendData[16];
void setup()
{
    Serial.begin(9600);
    for(int i = 0; i < 3 ; i++)
        pinMode(buttons[i], INPUT);

  //Configure RF
    vw_set_ptt_inverted(true);
    vw_set_tx_pin(RFData);
    vw_setup(2000);// speed of data transfer Kbps
}

void loop()
{
  x = analogRead(AxisX);
  y = analogRead(AxisY);
  itoa(x,xCharMsg,10);
  itoa(y,yCharMsg,10);

  sprintf(sendData, "%d,%d,%d,%d,%d", x, y, digitalRead(buttons[0]), digitalRead(buttons[1]),digitalRead(buttons[2]));
  Serial.println(sendData);
   /*  DEBUG
   Serial.print(estadoButtonsChazr);
  Serial.print("Sensor1 Integer: ");
  Serial.print(sendData);
  Serial.print(" Sensor1 CharMsg: ");
  Serial.print(xCharMsg[0]);
  Serial.println(" ");
  delay(1000);
  */
  //Serial.println("botoes:"); Serial.println(estadoButtonsChar);
  //Serial.println("eixo x:"); Serial.println(xCharMsg);
  //Serial.println("eixo y:"); Serial.println(yCharMsg);
  vw_send((uint8_t *)sendData, strlen(sendData));
  vw_wait_tx(); // Wait until the whole message is gone
  delay(10);
}
