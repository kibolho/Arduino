int LDR; //Variável para a leitura do LDR
int cont; //Variável utilizada para armazenar os valores lidos pelo sensor
int i; //Variável para contagem

void setup()
{
  Serial.begin(9600); //Inicia a serial
}
void loop()
{
  LDR=0; //Zera a variável LDR
  for(i=0;i<=10;i++) //Faz 10 vezes a leitura do sensor
  {
    cont=analogRead(A1); //Lê o valor do sensor (LDR ligado ao pino A0) e guarda na variável LDR
    LDR = LDR+cont; //Armazenamento na varíavel LDR o valor lido + o valor anterior
    delay(10); //Delay se 10 milissegundos
  }
  LDR=LDR/10; //Divide o valor armazenado por 10
  Serial.println(LDR); //Imprime o valor do LDR
    delay(2000);
}
