int bocina = 13;
int tipo = -1;
int segundos = 0;
String buffer = "";
bool esperandoTiempo = false;

void setup() {
  Serial.begin(115200);
  pinMode(bocina, OUTPUT);

  menu();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (esperandoTiempo && buffer.length() > 0) {
        segundos = buffer.toInt();
        if (segundos > 0) {
          sonar(tipo, segundos);
        } else {
          Serial.println("Tiempo no válido.");
        }
        esperandoTiempo = false;
        buffer = "";
        menu();
      }
      return;
    }

    if (esperandoTiempo) {
      if (isDigit(c)) buffer += c;
    } else {
      if (c == '0' || c == '1' || c == '2') {
        tipo = c - '0';
        Serial.print("¿Cuántos segundos? ");
        esperandoTiempo = true;
        buffer = "";
      } else {
        Serial.println("Opción no válida.");
        menu();
      }
    }
  }
}

void menu() {
  Serial.println("0 - Grave");
  Serial.println("1 - Medio");
  Serial.println("2 - Agudo");
}

void sonar(int t, int s) {
  int f = 0;
  if (t == 0) f = 300;
  else if (t == 1) f = 800;
  else if (t == 2) f = 2000;
  else return;

  tone(bocina, f);
  delay(s * 1000);
  noTone(bocina);
}