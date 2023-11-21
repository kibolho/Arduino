String test = "1010101010101";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   // put your main code here, to run repeatedly:
  String s1 = test.substring(5,12);
  String s2 = test.substring(0,4);
  Serial.println(s1);
  Serial.println(s2);
  char c1[8]="00000000";
  char c2[8]="00000000";
  s1.toCharArray(c1, 8);
  s2.toCharArray(c2, 8);
  Serial.println(c1);
  Serial.println(c2);
  int i1=0,i2=0;
  for (int i=0; i< strlen(c1); i++)  // for every character in the string  strlen(s) returns the length of a char array
  {
    i1 *= 2; // double the result so far
    if (c1[i] == '1') i1++;  //add 1 if needed
  }
  for (int i=0; i< strlen(c2); i++)  // for every character in the string  strlen(s) returns the length of a char array
  {
    i2 *= 2; // double the result so far
    if (c2[i] == '1') i2++;  //add 1 if needed
  }  
  Serial.println(i1,BIN);
  Serial.println(i2,BIN);
}

void loop() {
 
}
