// Definir los pines de salida compatibles con ESP32-C6
#define PIN_WAVE1 4
#define PIN_WAVE2 5

// Definir los periodos de las ondas en microsegundos
#define PERIOD_WAVE1 1000  // 1 kHz -> 1 ms
#define PERIOD_WAVE2 500   // 2 kHz -> 0.5 ms

void waveTask1(void *pvParameters) {
    while (1) {
        digitalWrite(PIN_WAVE1, !digitalRead(PIN_WAVE1)); // Alternar estado
        delayMicroseconds(PERIOD_WAVE1 / 2);
    }
}

void waveTask2(void *pvParameters) {
    while (1) {
        digitalWrite(PIN_WAVE2, !digitalRead(PIN_WAVE2)); // Alternar estado
        delayMicroseconds(PERIOD_WAVE2 / 2);
    }
}

void setup() {
    pinMode(PIN_WAVE1, OUTPUT);
    pinMode(PIN_WAVE2, OUTPUT);
    
    xTaskCreatePinnedToCore(waveTask1, "Wave1", 1000, NULL, 1, NULL, 0); // Core 0
    xTaskCreatePinnedToCore(waveTask2, "Wave2", 1000, NULL, 1, NULL, 1); // Core 1
}

void loop() {
    // Nada en el loop principal
}
