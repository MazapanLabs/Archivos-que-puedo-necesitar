#define transistor 14
#define transitor 13  

void setup() {
  pinMode(sobsta , INPUT);
  pinMode(transistor, OUTPUT);
  digitalWrite(transistor, LOW); 
}

void loop() {
  int obstaculo = digitalRead(transistor);
  if (obstaculo== HIGH) {
    digitalWrite(transistor, HIGH); 
  } else {
    digitalWrite(transistor, LOW); 
  }

  delay(100); 
}