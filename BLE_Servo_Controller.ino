#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define INCLUDE_DABBLEINPUTS_MODULE
#define Baud_Rate 9600

#include <Servo.h>
#include <Dabble.h>
#include <SoftwareSerial.h>

Servo servo0;
int LED = 13;
int s0A = 0;
SoftwareSerial BLE_Shield(4,5);

void setup() {
  //set BAUD rate
  Serial.begin(Baud_Rate);
  Dabble.begin(Baud_Rate);
  BLE_Shield.begin(Baud_Rate);

  //visual LED to indicate function
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(9, OUTPUT);

  //setup servos
  servo0.attach(9);
  servo0.write(0);
  
  //test if BLE is listening
  if (BLE_Shield.isListening()){
    Serial.println("Device is listening.");
  }
}

void loop() {
  //refresh smartphone input
  Dabble.processInput();
  if(GamePad.isUpPressed()){
    Serial.println("Up");
    s0A+=25;
    servo0.write(s0A);
  }
  if(GamePad.isDownPressed()){
    Serial.println("Down");
    s0A-=25;
    servo0.write(s0A);
  }
  
}
