String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    // put your main code here, to run repeatedly:
  String test = "90a23a32";
  String x=getValue(test,'a',0);
  Serial.println(x);
  Serial.println(x.toFloat());
  String y=getValue(test,'a',1);
  Serial.println(y);
  Serial.println(y.toFloat());
  String z=getValue(test,'a',2);
  Serial.println(z);
  Serial.println(z.toFloat());
  Serial.println();


  
float AngModRoll,AngModPitch,AngModYaw;
  char value[10]="100a23b32c";
  char buf[3];
  int j=0;
  int size_msg = strlen( (const char* ) value)-3;
  Serial.println(size_msg);
  for (int i=0;i<size_msg;i++){
    Serial.print("index");
    Serial.print(i);
    Serial.print("=");
    Serial.println(value[i]);
    if (value[i]=='a'){
      AngModRoll=atof(buf);
      j=0;
      memset(buf, 0, sizeof(buf));
    }else if (value[i]=='b'){
      AngModPitch=atof(buf);
      j=0;
      memset(buf, 0, sizeof(buf));
    }else if(value[i]=='c'){
      AngModYaw=atof(buf);
    }else{
      buf[j]=value[i];
      j++;
    }
  }
  Serial.println(AngModRoll);
  Serial.println(AngModPitch);
  Serial.println(AngModYaw);
  
}

void loop() {

  
}
