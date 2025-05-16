// Definir los pines del LED y el botón
int ledPin = 10;      // Pin donde está el LED
int buttonPin = 11;   // Pin donde está el botón

bool ledState = false;  // Estado del LED (apagado inicialmente)
bool lastButtonState = LOW;  // Estado anterior del botón
bool buttonState = LOW;  // Estado actual del botón

void setup() {
  // Inicializar el pin del LED como salida
  pinMode(ledPin, OUTPUT);

  // Inicializar el pin del botón como entrada
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Leer el estado actual del botón
  buttonState = digitalRead(buttonPin);

  // Detectar el cambio de estado (presión del botón)
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Invertir el estado del LED cada vez que se presiona el botón
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW); // Enciende o apaga el LED

    // Esperar un pequeño tiempo para evitar rebotes del botón
    delay(200);  // Delay de 200 ms
  }

  // Guardar el estado actual del botón para la próxima iteración
  lastButtonState = buttonState;
}