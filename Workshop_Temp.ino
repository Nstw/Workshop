#include <dht.h>
#define DHT11 2

dht DHT;
int dhtTemp;
int temperature;

void setup() {
  Serial.begin(9600);
}

void loop() {
   dhtTemp = DHT.read11(DHT11);
   temperature = (int) DHT.temperature;

  Serial.print("temperature = ");
  Serial.println(temperature);
  delay(1000);
}
