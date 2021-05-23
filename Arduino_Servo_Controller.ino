#include <Servo.h>

int LED = 13;
Servo myServo;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  myServo.attach(9);
  myServo.write(0);
}

void loop() {
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
  digitalWrite(LED, HIGH);
}
