#define LED 3

bool isPeople = true;
bool isAirOn;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() 
{
  if(isPeople == 1)
  {
    digitalWrite(LED, HIGH);
    isAirOn = true;
    Serial.print("Air Conditioner: ON");
  }
  else
  {
    digitalWrite(LED, LOW);
    isAirOn = false;
    Serial.print("Air Conditioner: OFF");
  }
  delay(200);
}
