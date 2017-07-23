#include <Servo.h> 
#define TRIGGER           3
#define ECHO_DOOR_FRONT   5
#define ECHO_DOOR_IN      6
Servo SERVO;  
unsigned long distFRONT;
unsigned long distIN;
unsigned long curTime;
int people =0;
bool IS_PEOPLE_IN = false;
bool IS_DOOR_OPEN = false;
bool StandFRONT = false;
bool StandIN = false;
void CheckPeople()
{
  if(people>=1)
  {
    IS_PEOPLE_IN = true;
    return 1;
  }
  else 
  {
    IS_PEOPLE_IN = false;
    return 0;
  }
}
void CheckFRONT()
{
  if(distIN<=5)
  {
    StandFRONT = true;
    OpenDoor();
    Serial.print("Door: Open");
    if(distIN<=5 && StandFRONT)
    {
      delay(150);
      CloseDoor();
      Serial.print("Door: Close");
      StandFRONT = false;
      delay(200);
      people+=1;
    }
  }
}
void CheckIN()
{
  if(distIN<=5)
  {
    StandIN = true;
    OpenDoor();
    Serial.print("Door: Open");
    if(distFRONT<=5 && StandIN)
    {
      delay(150);
      CloseDoor();
      Serial.print("Door: Close");
      StandIN = false;
      delay(200);
      people-=1;
    }
  }
}

void OpenDoor()
{
  SERVO.write(0);  
}
void CloseDoor()
{
  SERVO.write(90);
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO_DOOR_FRONT,INPUT);
  pinMode(ECHO_DOOR_IN, INPUT);
  IS_PEOPLE_IN = false;
  StandFRONT = false;
  StandIN = false;
  SERVO.attach(7);
}
inline void sendTrigger() 
{
  digitalWrite(TRIGGER, LOW);
  delay(2);
  digitalWrite(TRIGGER, HIGH);
  delay(2);
  digitalWrite(TRIGGER, LOW);
}

unsigned long mLogTime;
void loop() 
{
  sendTrigger();
  distFRONT = pulseIn(ECHO_DOOR_FRONT, HIGH) / 74 / 2;
  delay(100);
  
  sendTrigger();
  distIN = pulseIn(ECHO_DOOR_IN, HIGH) / 74 / 2;
  curTime = millis();
  if (curTime - mLogTime > 1000) 
  {
    Serial.print("front: ");
    Serial.println(distFRONT);
    Serial.print("in: ");
    Serial.println(distIN);
    mLogTime = curTime;
  }
}
