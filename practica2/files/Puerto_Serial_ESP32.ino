#define RX_PIN 16
#define TX_PIN 17

void setup() {
  Serial.begin(115200);   // UART por USB para debug
  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // UART físico

  Serial.println("ESP32-C6: Comunicación Serial iniciada");
}

void loop() {
  Serial1.println("Mensaje desde ESP32-C6 en UART1");
  delay(1000);
}