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
  if(distFRONT<=5)
  {
    StandFRONT = true;
    OpenDoor();
    IS_DOOR_OPEN = true;
    Serial.print("Door: Open\n");
    if(distIN<=5 && StandFRONT)
    {
      delay(150);
      CloseDoor();
      IS_DOOR_OPEN = false;
      Serial.print("Door: Close\n");
      StandFRONT = false;
      delay(200);
      people+=1;
    }
    StandFRONT = false;
  }
}
void CheckIN()
{
  if(distIN<=5)
  {
    StandIN = true;
    OpenDoor();
    IS_DOOR_OPEN = true;
    Serial.print("Door: Open\n");
    if(distFRONT<=5 && StandIN)
    {
      delay(150);
      CloseDoor();
      IS_DOOR_OPEN = false;
      Serial.print("Door: Close\n");
      StandIN = false;
      delay(200);
      people-=1;
    }
    StandIN = false;
  }
}

void OpenDoor()
{
  if(IS_DOOR_OPEN)
  {
    
  }
  else
  {
    SERVO.write(0);
    IS_DOOR_OPEN = true;
  }
}
void CloseDoor()
{
    if(IS_DOOR_OPEN)
  {
    SERVO.write(90);
    IS_DOOR_OPEN = false;
  }
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
  SERVO.attach(9);
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
    CheckFRONT();
    Serial.print("front: ");
    Serial.println(distFRONT);
    CheckIN();
    Serial.print("in: ");
    Serial.println(distIN);
    mLogTime = curTime;
  }
}
