#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define Baud_Rate 9600

#include <Servo.h>
#include <Dabble.h>

//servos, s2/s3 are high-torque
Servo s0, s1, s2, s3;
int LED = 13;
int s0A = 0, s1A = 0, s2A = 0, s3A = 0;
bool bytesWereRead = false;
char c = ' ';
boolean NL = true;
//sensitivity factor
int sFactor = 1;

void setup() {
  //set BAUD rate
  Serial.begin(Baud_Rate);
  Dabble.begin(Baud_Rate);

  //visual LED to indicate function
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  //setup servos
  s0.attach(9);
  s0.write(0);
  s1.attach(10);
  s1.write(0);
  s2.attach(11);
  s2.write(0);
  s3.attach(12);
  s3.write(0);
}

void loop() {
  //refresh smartphone input
  Dabble.processInput();
  //decrease speed, increase precision
  if(GamePad.isStartPressed() && sFactor > 1){
    Serial.println("Speed Decreased");
    delay(200);
    sFactor-=1;
  }
  //increase speed, decrease precision
  if(GamePad.isSelectPressed() && sFactor < 10){
    Serial.println("Speed Increased");
    delay(200);
    sFactor+=1;
  }
  //increase s2 angle
  if(GamePad.isSquarePressed() && s2A<180){
    Serial.println("Square");
    s2A+=(sFactor);
    s2.write(s2A);
    delay(20);
  }
  //decrease s2 angle
  if(GamePad.isCirclePressed() && s2A>0){
    Serial.println("Circle");
    s2A-=(sFactor);
    s2.write(s2A);
    delay(20);
  }
  //increase s3 angle
  if(GamePad.isTrianglePressed() && s3A<180){
    Serial.println("Triangle");
    s3A+=(sFactor);
    s3.write(s3A);
    delay(20);
  }
  //decrease s3 angle
  if(GamePad.isCrossPressed() && s3A>0){
    Serial.println("Cross");
    s3A-=(sFactor);
    s3.write(s3A);
    delay(20);
  }
  //increase s0 angle
  if(GamePad.isUpPressed() && s0A<180){
    Serial.println("Up");
    s0A+=(sFactor);
    s0.write(s0A);
    delay(20);
  }
  //decrease s0 angle
  if(GamePad.isDownPressed() && s0A>0){
    Serial.println("Down");
    s0A-=(sFactor);
    s0.write(s0A);
    delay(20);
  }
  //increase s1 angle
  if(GamePad.isLeftPressed() && s1A<180){
    Serial.println("Left");
    s1A+=(sFactor);
    s1.write(s1A);
    delay(20);
  }
  //decrease s1 angle
  if(GamePad.isRightPressed() && s1A>0){
    Serial.println("Right");
    s1A-=(sFactor);
    s1.write(s1A);
    delay(20);
  }
  
}
