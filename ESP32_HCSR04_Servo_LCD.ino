#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pines HC-SR04
#define TRIG_PIN  26
#define ECHO_PIN  25

// Pines Servos
#define SERVO1_PIN 13
#define SERVO2_PIN 14

// Variables
long duration;
float distance;

// Servos
Servo servo1;
Servo servo2;

// LCD I2C dirección 0x27 (puede ser 0x3F en algunos módulos)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Inicializar pines sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inicializar servos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo1.write(0); // Inicialmente en 0°
  servo2.write(0);

  // Inicializar LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Iniciando...");
  delay(1000);
}

void loop() {
  // Medir distancia
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  distance = duration * 0.0343 / 2;

  // Limpiar LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance, 1);
  lcd.print(" cm");

  // Lógica de servos
  if (distance > 4 && distance < 6) {
    servo1.write(45);
    servo2.write(0);
    lcd.setCursor(0, 1);
    lcd.print("Servo1 (13): 45gr");
  }
  else if (distance > 9 && distance < 11) {
    servo1.write(0);
    servo2.write(45);
    lcd.setCursor(0, 1);
    lcd.print("Servo2 (14): 45gr");
  }
  else {
    servo1.write(0);
    servo2.write(0);
    lcd.setCursor(0, 1);
    lcd.print("Servo: ninguno ");
  }

  delay(500); // Actualización cada medio segundo
}