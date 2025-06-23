// incluir librería para leer y escribir en la memoria flash
#include <EEPROM.h>
// definir el número de bytes que quieres acceder
#define EEPROM_SIZE 1
// las constantes no cambiarán. Se usan aquí para establecer los números de pin:
const int buttonPin = 4;
// el número del pin del botón pulsador
const int ledPin = 18;
// el número del pin del LED
// Las variables cambiarán:
int ledState = HIGH;
// el estado actual del pin de salida
int buttonState;
// la lectura actual del pin de entrada
int lastButtonState = LOW;
// la lectura anterior del pin de entrada
// las siguientes variables son unsigned longs porque el tiempo, medido en
// milisegundos, rápidamente se volverá un número más grande del que puede almacenar un int.
unsigned long lastDebounceTime = 0; // la última vez que se cambió el pin de salida
unsigned long debounceDelay = 50; // el tiempo de rebote; aumenta si la salida parpadea

void setup () {
  Serial.begin (115200);
  // inicializar EEPROM con el tamaño predefinido
  EEPROM.begin (EEPROM_SIZE);
  pinMode (buttonPin, INPUT);
  pinMode (ledPin, OUTPUT);
  // leer el último estado del LED de la memoria flash
  ledState = EEPROM.read (0);
  // establecer el LED al último estado almacenado
  digitalWrite (ledPin, ledState);
  buttonState = digitalRead(buttonPin);
  lastButtonState = buttonState;
}

void loop () {
  // leer el estado del interruptor en una variable local:
  int reading = digitalRead (buttonPin);

  // verificar si acabas de presionar el botón
  // (es decir, la entrada pasó de LOW a HIGH), y has esperado lo suficiente
  // desde la última pulsación para ignorar cualquier ruido:
  // Si el interruptor cambió, debido a ruido o pulsación:
  if (reading != lastButtonState) {
    // reiniciar el temporizador de rebote
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // sea cual sea la lectura, ha estado así por más tiempo que el retardo de rebote,
    // así que tómalo como el estado actual real:
    // si el estado del botón ha cambiado:
    if (reading != buttonState) {
      buttonState = reading;
      // solo alterna el LED si el nuevo estado del botón es HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        // si la variable ledState es diferente del estado actual del LED
        if (digitalRead (ledPin) != ledState) {
          Serial.println ("Estado cambiado");
          // cambiar el estado del LED
          digitalWrite (ledPin, ledState);
          // guardar el estado del LED en la memoria flash
          EEPROM.write (0, ledState);
          EEPROM.commit();
          Serial.println ("Estado guardado en la memoria flash");
        }
      }
    }
  }
  // guardar la lectura. La próxima vez será lastButtonState:
  lastButtonState = reading;
}
