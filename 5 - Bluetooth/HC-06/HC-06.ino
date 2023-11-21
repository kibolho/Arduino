int led = 13;
/* used help from http://byron76.blogspot.com/2011/09/one-board-several-firmwares.html */
void setup() { 
 pinMode(led, OUTPUT);
 Serial.begin(115200);
 Serial1.begin(115200);//use 9600 if first set up
}
void loop() {
 digitalWrite(led, HIGH);//sanity check
 command("AT",2);// response: OK
 command("AT+VERSION",12);// response: OKlinvorV1.5
 command("AT+NAMEArduino",9);//response: OKsetname
 command("AT+BAUD8",8);//response: OK115200
 while(1);//stop execution
}
void command(const char* cmd, int num_bytes_response) {
 delay(1000);
 Serial1.print(cmd);
 delay(1500);
 for (int i=0;i<num_bytes_response;i++)
 Serial.write(Serial1.read());
}
