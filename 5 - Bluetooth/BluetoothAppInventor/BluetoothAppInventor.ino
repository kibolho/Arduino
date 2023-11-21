char cmd;
char param;
String param2;
#define max_char 10
char message[max_char];    // stores you message
char r_char;               // reads each character
byte index = 0;            // defines the position into your array
int i;
bool messageEnd = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//Bluetooth
  Serial1.begin(9600);//Bluetooth
}

void loop() {
}

void serialEvent1() {
  //Serial.println("Recebeu");
  //while is reading the message
  Serial1.println("oi");
  Serial.println("oi");
  while (Serial1.available() > 0) {
    //the message can have up to 100 characters
    if (index < (max_char - 1))
    {
      r_char = Serial1.read();      // Reads a character
      //Serial.print(r_char);
      message[index] = r_char;     // Stores the character in message array
      index++;                     // Increment position
      message[index] = '\0';       // Delete the last position
      if(r_char=='z'){
        messageEnd=true;
      }
    }
  }
  if (messageEnd) {
    Serial.println(message);
    switch (message[0]) {
      case '1':
        // First byte contains a generic "command" byte. We arbitrarily defined '1' as the command to then check the 2nd parameter byte
        // User can additional commands by adding case 2, 3, 4, etc
        {
          Serial.println("Comando1");
          // read the parameter byte
          param = message[1];
          Serial.print("Param = ");
          Serial.println(param);
          switch (param)
          {
            case 'f':
              Serial.println("Frente");
              break;
            case 'd':
              Serial.println("Direita");
              break;
            case 'e':
              Serial.println("Esquerda");
              break;
            case 'a':
              Serial.println("Trás");
              break;
            case 'p':
              Serial.println("Parar");
              break;
            default: break; // do nothing
          }// switch (param)
        } break; // switch (cmd) case 1
      case '2':
        {
          param = message[1];
          Serial.print("Param = ");
          Serial.println(param);
          switch (param)
          {
            case 'f':
              Serial.println("Frente");
              for(int a=2;a<(index-1);a++){
                param2.concat(message[a]);
              }
              Serial.print("Param2 = ");
              Serial.println(param2.toInt());
              break;
            case 'd':
              Serial.println("Direita");
             for(int a=2;a<(index-1);a++){
                param2.concat(message[a]);
              }
              Serial.print("Param2 = ");
              Serial.println(param2.toInt());
              break;
            case 'e':
              Serial.println("Esquerda");
              for(int a=2;a<(index-1);a++){
                param2.concat(message[a]);
              }
              Serial.print("Param2 = ");
              Serial.println(param2.toInt());
              break;
            case 'a':
              Serial.println("Tras");
              for(int a=2;a<(index-1);a++){
                param2.concat(message[a]);
              }
              Serial.print("Param2 = ");
              Serial.println(param2.toInt());
              break;
            default: break; // do nothing
          } // switch (param)
        }
      default: break; // do nothing
    }
    for (i = 0; i < max_char; i++) {
      message[i] = '\0';
    }
    //resests the index
    index = 0;
    messageEnd=false;
    param2="";
  }
}
