void setup() {
  Serial.begin(115200);
  
  unsigned long inicio = millis();
  volatile unsigned long suma = 0;
  
  for (unsigned long i = 0; i < 1000000; i++) {
    suma += i;
  }

  unsigned long fin = millis();
  Serial.print("Tiempo tomado en ms: ");
  Serial.println(fin - inicio);
}

void loop() {}