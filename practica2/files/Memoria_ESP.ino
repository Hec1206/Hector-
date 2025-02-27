#include "EEPROM.h"

const char mensaje[] PROGMEM = "ESP32-C6 usando Flash";  // Almacenado en Flash
char buffer[50000];  // Usa SRAM

void setup() {
  Serial.begin(115200);
  
  // Simular EEPROM con Flash
  EEPROM.begin(512);
  EEPROM.write(0, 99);
  EEPROM.commit();

  Serial.println("ESP32-C6: Prueba de memoria");
  Serial.print("Valor en EEPROM simulada: ");
  Serial.println(EEPROM.read(0));

  Serial.print("Memoria SRAM libre: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
}

void loop() {}