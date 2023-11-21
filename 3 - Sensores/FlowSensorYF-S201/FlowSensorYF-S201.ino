/*
 * Includes
 */
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define PIN_SENSOR            0
 
//general variables 
long SensorPulseCounter=1;
float CalculatedFlow=0.0;
float CalculatedConsumption=0.0; 
long PulsosPerLitter=0.0;   //contains how much pulses of sensor indicates 1l of consumption
unsigned long LastMillis=0.0;   //used to time-slice processing
char CalibrationMode;   //indicates if board it's in calibration mode
/*
 * Prototypes
 */
void CountSensorPulses(void);
void ResetCountSensorPulses(void);
void CalculateFlowAndConsumption(void);

void TurnOnSensorPulseCounting(void);
void TurnOffSensorPulseCounting(void);

/*
 * Implementation / functions
 */
 
//Function: counts pulses of water flow sensor
//Params: none
//Return: none 
void CountSensorPulses(void)
{
    SensorPulseCounter++;      
}
 
//Function: reset counter of water flow sensor pulses
//Params: none
//Return: none 
void ResetCountSensorPulses(void)
{  
    SensorPulseCounter = 0;
}
 
//Function: calculate water instant flow and consumption
//Params: none
//Return: none 
void CalculateFlowAndConsumption(void)
{
 
    //calculation begins!    
    CalculatedFlow = (float)((float)SensorPulseCounter / (float)PulsosPerLitter);  //Flow in l/s
  
    CalculatedConsumption = CalculatedConsumption + CalculatedFlow;   //sum consumption of 1 second
    CalculatedFlow = CalculatedFlow*3600.0;   //Flow in l/h       
}
 
//Function: turn on sensor counting pulses
//Params: none
//Return: none
void TurnOnSensorPulseCounting(void)
{
    //this function allows pulse counter reset only if sensor it's already calibrated
    ResetCountSensorPulses();
     
    //attach sensor pin's interrup (rising edge)
    attachInterrupt(digitalPinToInterrupt(PIN_SENSOR), CountSensorPulses, RISING);
}
 
//Function: turn on sensor counting pulses
//Params: none
//Return: none
void TurnOffSensorPulseCounting(void)
{
    detachInterrupt(digitalPinToInterrupt(PIN_SENSOR));
}

//Setup function. Here the inits are made!
void setup() 
{
    Serial.begin(9600);

      // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,1);
    // Print a message to the LCD.
    lcd.print("Flow Sensor!");
  
    //variables init
    ResetCountSensorPulses();
    CalculatedFlow = 0.0;
    CalculatedConsumption = 0.0;
     
    //configure sensor pin as input
    pinMode(PIN_SENSOR, INPUT);
 
    //start counting sensor's pulses 
    TurnOnSensorPulseCounting();
    LastMillis = millis();
}
 
//main loop / main program
void loop() 
{        
    if ((millis() - LastMillis) >= 1000)
    {
        lcd.setCursor(0,1);
        lcd.print("Flow="); 
        lcd.print(CalculatedFlow,1);
        lcd.print("Con=");
        lcd.print(CalculatedConsumption,1);
        Serial.print("Flow="); 
        Serial.print(CalculatedFlow,1);
        Serial.print(" Con=");
        Serial.println(CalculatedConsumption,1);
        //to avoid calculation errors, the sensor pulse acquisition is disabled
        //during all calculation     
        TurnOffSensorPulseCounting();
         
        //calculate water and flow consumption
        CalculateFlowAndConsumption();
    
         //reset time-slice processing
        LastMillis = millis();    
         
        //calculation and sending data is complete! Sensor pulse acquisition starts again        
        TurnOnSensorPulseCounting();
    }
}
