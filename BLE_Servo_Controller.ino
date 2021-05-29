#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define Baud_Rate 9600

#include <Servo.h>
#include <Dabble.h>

//s0 is shoulder, s1 is elbow, s2 rotates hand, s3 grips
Servo s0, s1, s2, s3;
//angles of servos
int s0A = 0, s1A = 0, s2A = 0, s3A = 0;
int LED = 13;
bool bytesWereRead = false;
char c = ' ';
boolean NL = true;
//sensitivity factor, AKA speed of movement of robot
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

//increase given servo angle
void increaseAngle(Servo *servo, int &angle){
  if(angle<180){
    angle+=sFactor;
    servo->write(angle);
    delay(20);  
  }
}

//decrease given servo angle
void decreaseAngle(Servo *servo, int &angle){
  if(angle>0){  
    angle-=sFactor;
    servo->write(angle);
    delay(20);  
  }
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
  //move shoulder up
  if(GamePad.isUpPressed()){
    Serial.println("Up");
    increaseAngle(&s0, s0A);
  }
  //move shoulder down
  if(GamePad.isDownPressed()){
    Serial.println("Down");
    decreaseAngle(&s0, s0A);
  }
  //move elbow up
  if(GamePad.isLeftPressed() && s1A<180){
    Serial.println("Left");
    increaseAngle(&s1, s1A);
  }
  //move elbow down
  if(GamePad.isRightPressed() && s1A>0){
    Serial.println("Right");
    decreaseAngle(&s1, s1A);
  }
  //rotate hand clockwise
  if(GamePad.isSquarePressed()){
    Serial.println("Square");
    increaseAngle(&s2, s2A);
  }
  //rotate hand counter-clockwise
  if(GamePad.isCirclePressed()){
    Serial.println("Circle");
    decreaseAngle(&s2, s2A);
  }
  //tighten grip
  if(GamePad.isTrianglePressed()){
    Serial.println("Triangle");
    increaseAngle(&s3, s3A);
  }
  //loosen grip
  if(GamePad.isCrossPressed()){
    Serial.println("Cross");
    decreaseAngle(&s3, s3A);
  }
}
