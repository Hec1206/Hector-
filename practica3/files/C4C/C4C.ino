sensor:
esp32:
#include <WiFi.h>
#include <PubSubClient.h>
// WiFi
const char* ssid = "Guty";  
const char* password = "123456789";
// MQTT
const char* mqtt_server = "test.mosquitto.org";
const char* topic = "elementos2/augusto";
WiFiClient espClient;
PubSubClient client(espClient);
// Pin del potenciómetro
const int potPin = 4;
void setup() {
  Serial.begin(115200);
  delay(1000);
  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi");
  // Configurar MQTT
  client.setServer(mqtt_server, 1883);
  reconnect();
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // Leer el valor del potenciómetro
  int potValue = analogRead(potPin);
  char message[10];
  sprintf(message, "%d", potValue);
  // Enviar por MQTT
  client.publish(topic, message);
  Serial.print("Valor del potenciómetro enviado: ");
  Serial.println(potValue);
  delay(1000);  // Enviar cada 1 segundo
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando a MQTT...");
    if (client.connect("ESP32C6_PotClient")) {
      Serial.println("Conectado al broker MQTT");
    } else {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      Serial.println(" reintentando en 5 segundos");
      delay(5000);
    }
  }
}
