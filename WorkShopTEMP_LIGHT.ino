#define LED 2
#define LIGHT A0
//----------------
#include <dht.h>
#define DHT11 5
//----------------

//----------------
int lightInput;
//----------------
dht DHT;
int dhtTemp;
int temperature;
//----------------

void setup() {
  Serial.begin(9600);
  //-----------------------
  pinMode(LIGHT, INPUT);
  pinMode(LED, OUTPUT);
  //-----------------------
  
}

void loop() {
  //LIGHT--------------------------
  lightInput = analogRead(LIGHT);
  if(lightInput < 500){
    digitalWrite(LED, LOW);
  }
  else{
    digitalWrite(LED, HIGH);
  }
    Serial.print("Light Intensity: ");
    Serial.println(lightInput);
  //TEMPERATURE--------------------
  dhtTemp = DHT.read11(DHT11);
   temperature = (int) DHT.temperature;
  Serial.println(temperature);
  Serial.print("degree\n");
  //-------------------------------
}
