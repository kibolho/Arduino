#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

/* Device credentials */
char* deviceId = "54663b17eb98e809b2000005"; // set your device id (will be the MQTT client username)
char* deviceSecret = "wNauiTxIreJsYlnVqu5A4+4nKb1dVQ51"; // set your device secret (will be the MQTT client password)

/* Device topics */
char* outTopic = "devices/54663b17eb98e809b2000005/set"; // where physical updates are published
char* inTopic = "devices/54663b17eb98e809b2000005/get";  // where lelylan updates are received

/* Access settings */
byte server[] = { 96, 126, 109, 170 }; // MQTT server address
char* clientId = "2929292191"; // MQTT client id (random, max 23 bytes)

/* Sample payload published to lelylan */
/* Status-id is the basic light status id (http://types.lelylan.com/types/518be107ef539711af000001) */
char* payloadOn  = "{\"properties\":[{\"id\":\"518be5a700045e1521000001\",\"value\":\"on\"}]}";
char* payloadOff = "{\"properties\":[{\"id\":\"518be5a700045e1521000001\",\"value\":\"off\"}]}";

/* Ethernet configuration */
byte mac[] = { 0xA0, 0xA0, 0xBA, 0xAC, 0xAE, 0x12 };
EthernetClient ethClient;

/* MQTT communication */
void callback(char* topic, byte* payload, unsigned int length); // subscription callback
PubSubClient client(server, 1883, callback, ethClient);         // mqtt client

/* Pins configuration */
int inPin = 2; // button
int outPin = 4; // led

/* Button and led logics */
int state = HIGH;     // current state of the output pin
int reading;          // current reading from the input pin
int previous = LOW;   // previous reading from the input pin
long time = 0;        // the last time the output pin was toggled
long debounce = 200;  // the debounce time, increase if the output flickers

/* arduino setup */
void setup() {
  Serial.begin(9600);
  delay(500);

  Ethernet.begin(mac);
  Serial.print("Connected with IP: ");
  Serial.println(Ethernet.localIP());

  lelylanConnection();      // MQTT server connection
  pinMode(inPin, INPUT);    // button pin setup
  pinMode(outPin, OUTPUT);  // led pin setup
}

/* arduino loop */
void loop() {
  lelylanConnection();

  char* value;
  reading = digitalRead(inPin);  // read the button state

  // if the input just went from LOW and HIGH and we've waited long enough to ignore
  // any noise on the circuit, toggle the output pin and remember the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == LOW) {
      Serial.println("[PHYSICAL] Led turned on");
      lelylanPublish("on");
      state = HIGH;
    } else {
      Serial.println("[PHYSICAL] Led turned off");
      lelylanPublish("off");
      state = LOW;
    }

    time = millis();
  }

  // effectively update the light status
  digitalWrite(outPin, state);
  previous = reading;
}

/* MQTT server connection */
void lelylanConnection() {
  // add reconnection logics
  if (!client.connected()) {
    // connection to MQTT server
    if (client.connect(clientId, deviceId, deviceSecret)) {
      Serial.println("[PHYSICAL] Successfully connected with MQTT");
      lelylanSubscribe(); // topic subscription
    }
  }
  client.loop();
}

/* MQTT publish */
void lelylanPublish(char* value) {
  if (value == "on")
    client.publish(outTopic, payloadOn); // light on
  else
    client.publish(outTopic, payloadOff); // light off
}

/* MQTT subscribe */
void lelylanSubscribe() {
  client.subscribe(inTopic);
}

/* Receive Lelylan message and confirm the physical change */
void callback(char* topic, byte* payload, unsigned int length) {
  // copu the payload content into a char*
  char* json;
  json = (char*) malloc(length + 1);
  memcpy(json, payload, length);
  json[length] = '\0';

  // update the physical status and confirm the executed update
  if (String(payloadOn) == String(json)) {
    Serial.println("[LELYLAN] Led turned on");
    lelylanPublish("on");
    state = HIGH;
  } else {
    Serial.println("[LELYLAN] Led turned off");
    lelylanPublish("off");
    state = LOW;
  }

  digitalWrite(outPin, state);
  free(json);
}

