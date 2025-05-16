void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10, digitalRead(11));
}