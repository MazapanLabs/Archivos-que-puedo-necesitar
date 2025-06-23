#include <Arduino.h>

TaskHandle_t TaskBlink; 

volatile int contador = 0; 

#define led 13

void loop2(void *parameter){
  int ultimoContador = -1;
  for(;;){
    if (contador != ultimoContador) { 
      if (contador % 2 == 0) {
        digitalWrite(led, LOW);
        Serial.println("[loop2] Núcleo -> " + String(xPortGetCoreID()) + " | LED Apagado");
      } else {
        digitalWrite(led, HIGH);
        Serial.println("[loop2] Núcleo -> " + String(xPortGetCoreID()) + " | LED Encendido");
      }
      ultimoContador = contador;
    }
    vTaskDelay(10); 
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  
  xTaskCreatePinnedToCore(
    loop2,         
    "TaskBlink",   
    1000,          
    NULL,          
    1,             
    &TaskBlink,    
    0);            
}

void loop() {
  Serial.println("[loop principal] Núcleo -> " + String(xPortGetCoreID()) + " | Contador: " + String(contador));
  contador++;
  delay(1000); 
}