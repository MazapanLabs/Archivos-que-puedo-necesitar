#include <Ticker.h>

Ticker tpot;
Ticker tled;

#define LED 13
#define POT 34

int cuentaPot = 0;
const int limitePot = 5;
int cuentaLed = 0;
const int limiteLed = 10;

int estadoLed = 0; // 0 = apagado, 1 = encendido

void leerPot() {
  int valor = analogRead(POT);
  Serial.print("Pot: ");
  Serial.println(valor);
  cuentaPot++;
  if (cuentaPot >= limitePot) {
    Serial.println("Fin pot");
    tpot.detach();
  }
}

void parpadeoLed() {
  if (estadoLed == 0) {
    digitalWrite(LED, HIGH);
    Serial.println("Led ON");
    estadoLed = 1;
  } else {
    digitalWrite(LED, LOW);
    Serial.println("Led OFF");
    estadoLed = 0;
  }
  cuentaLed++;
  if (cuentaLed >= limiteLed) {
    tled.detach();
    digitalWrite(LED, LOW);
    Serial.println("Fin led");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Serial.println("Inicio");
  tpot.attach(2, leerPot);
  tled.attach(1, parpadeoLed);
}

void loop() {

}