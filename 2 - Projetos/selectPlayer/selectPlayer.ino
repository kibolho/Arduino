//entradas
int grupo1 = A0;
int grupo2 = A1;
int grupo3 = A2;
int grupo4 = A3;
int grupo5 = A6;
int grupo6 = A5;

//saidas
int out1 = 2;
int out2 = 3;
int out3 = 4;
int out4 = 5;
int out5 = 6;
int out6 = 7;

//reset
int reset = A7;

int code;
boolean check = false;

void setup() {    
  Serial.begin(9600);  
  // initialize the digital pin as an output.
  pinMode(grupo1, INPUT);  
  pinMode(grupo2, INPUT);  
  pinMode(grupo3, INPUT);  
  pinMode(grupo4, INPUT);  
  pinMode(grupo5, INPUT);  
  pinMode(grupo6, INPUT);  
  pinMode(reset, INPUT);  

  pinMode(out1, OUTPUT);     
  pinMode(out2, OUTPUT);   
  pinMode(out3, OUTPUT);   
  pinMode(out4, OUTPUT);   
  pinMode(out5, OUTPUT);   
  pinMode(out6, OUTPUT); 
  
   digitalWrite(out1, LOW);   
    digitalWrite(out2, LOW);  
     digitalWrite(out3, LOW);  
      digitalWrite(out4, LOW);  
       digitalWrite(out5, LOW);  
        digitalWrite(out6, LOW);  
        while(analogRead(grupo1)>400||analogRead(grupo2)>400||analogRead(grupo3)>400||analogRead(grupo4)>400||analogRead(grupo5)>400||analogRead(grupo6)>400){
                  Serial.println("7");
        }
   digitalWrite(out1, HIGH);   
    digitalWrite(out2, HIGH);  
     digitalWrite(out3, HIGH);  
      digitalWrite(out4, HIGH);  
      digitalWrite(out5, HIGH);  
      digitalWrite(out6, HIGH); 
      Serial.println("0"); 
        
        
}

// the loop routine runs over and over again forever:
void loop() {
    if(check==false){
       //Serial.println("FALSE");
      if(analogRead(grupo1)>600){
         code=1;
      }if(analogRead(grupo2)>600){
          code=2;
      }if(analogRead(grupo3)>600){
          code=3; 
      }if(analogRead(grupo4)>600){
          code=4;
      }if(analogRead(grupo5)>600){
          code=5;
      }if(analogRead(grupo6)>600){
          code=6;
      }
     switch (code){
        case 1:
          digitalWrite(out5, LOW);   // turn the LED on (HIGH is the voltage level)
          check=true;
          Serial.println("1");
          break;
        case 2:
         digitalWrite(out1, LOW); 
          check=true; 
          Serial.println("2");
           break;
        case 3:
         digitalWrite(out2, LOW);  
          check=true; 
          Serial.println("3");
           break;
        case 4:
         digitalWrite(out6, LOW);  
          check=true; 
          Serial.println("4");
           break;
        case 5:
        digitalWrite(out3, LOW);  
          check=true; 
          Serial.println("5");
           break;
        case 6:
        digitalWrite(out4, LOW);  
          check=true; 
          Serial.println("6");
           break;
      }
    }else{
      if(analogRead(reset)<400){
         digitalWrite(out1, LOW);   
         digitalWrite(out2, LOW);  
         digitalWrite(out3, LOW);  
         digitalWrite(out4, LOW);  
         digitalWrite(out5, LOW);  
         digitalWrite(out6, LOW);  
         while(analogRead(grupo1)>400||analogRead(grupo2)>400||analogRead(grupo3)>400||analogRead(grupo4)>400||analogRead(grupo5)>400||analogRead(grupo6)>400){
             Serial.println("7");
         }
             Serial.println("8");
         digitalWrite(out1, HIGH);   
         digitalWrite(out2, HIGH);  
         digitalWrite(out3, HIGH);  
         digitalWrite(out4, HIGH);  
         digitalWrite(out5, HIGH);  
         digitalWrite(out6, HIGH); 
         delay(1000);
         check=false; 
      } 
    }
}
