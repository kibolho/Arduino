//André Kuhn - Automation
//Código para o Dimmer ser controlado pelos botões

int loadR = 3;
volatile int power = 100;
float tempC;
int reading;
int tempPin = 0;

void setup() 
{
	pinMode(loadR, OUTPUT);
        
        //Inicializa interrupção. O número zero indica a porta 2 do arduino,
	//zero_cross_int é a função que será chamada toda vez que pino 2 do Aeduino,
	//"subir" (RISING) de valor de 0 para 1.
	attachInterrupt(0, zero_cross_int, RISING);
	
	pinMode(4, INPUT);
  pinMode(5, INPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}


void loop() 
{
    if(digitalRead(4) == HIGH)
    {
       if(power <= 300)
       {
          power += 10;
       }
        delay(200);
    }
    if(digitalRead(5) == HIGH)
    {
      if(power >= 20)
      {
        power -= 10;
      }
      delay(200);
   }
}

void zero_cross_int()
{

	//Cálculo do ângulo de disparo: 60Hz -> 8,33ms (1/2 ciclo)
	//(8333us - 8,33us) / 333 = 25 (aproximadamente)
        int powertime = (25*(333-power));
        if(powertime <= 325)
        {
          digitalWrite(loadR, HIGH);
        }	

        else if(powertime >= 8325)
        {
          digitalWrite(loadR, LOW);
        }
        
        else if((powertime > 0) && (powertime < 8325))
        {       
          //Mantém o circuito desligado por powertime microssegundos
      	  delayMicroseconds(powertime);
      	
      	  //Envia sinal ao TRIAC para que ele passe a conduzir
      	  digitalWrite(loadR, HIGH);
      	
      	  //Espera alguns microssegundos para que o TRIAC perceba o pulso
      	  delayMicroseconds(8.33);
              
                //Desliga o pulso
      	  digitalWrite(loadR, LOW);
        }        
}


