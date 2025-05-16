int ledPin = 15;


void setup() {
  pinMode(ledPin, OUTPUT);

}

void loop() {
  digitalWrite(15, HIGH);
  delay(700);
  digitalWrite(15, LOW);
  delay(700);
}
