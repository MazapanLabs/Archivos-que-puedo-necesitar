
#include <ESP32Tone.h>
#include <ESP32PWM.h>
#include <ESP32Servo.h>

#define SERVO 15
#define B1 32
#define B2 33
#define B3 18

Servo myservo;

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT); 
}

void loop() {
  if (digitalRead(B1) == HIGH) {
    myservo.write(15); 
    Serial.println("Servo a 15 grados");
    delay(300); 
  }
  if (digitalRead(B2) == HIGH) {
    myservo.write(45); 
    Serial.println("Servo a 45 grados");
    delay(300);
  }
  if (digitalRead(B3) == HIGH) {
    myservo.write(75); 
    Serial.println("Servo a 75 grados");
    delay(300);
  }
}