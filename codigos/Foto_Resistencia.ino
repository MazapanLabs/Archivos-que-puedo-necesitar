#define rele 13   
#define fotre 14 

void setup() {
  pinMode(rele, OUTPUT);
  pinMode(fotre,INPUT);
  digitalWrite(rele,LOW);
}

void loop() {
  int luz = digitalRead(fotre);
  if (luz== HIGH) {
    digitalWrite(rele, LOW); 
  } else {
    digitalWrite(rele, HIGH); 
  }

  delay(100); 
}