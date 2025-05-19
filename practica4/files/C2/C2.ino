#include <WiFi.h>           // Para ESP8266 usa <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Phone de Hectorin";       
const char* password = "12345678";
const char* mqtt_broker = "test.mosquitto.org"; // Broker público

const char* topic = "elementos2/hector/";
const int numMessages = 20;
unsigned long sendTimes[numMessages];
float latencies[numMessages];

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    unsigned long receivedTime = millis();
    
    String message = "";
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    int index = message.substring(4).toInt();
    if (index >= 0 && index < numMessages) {
        latencies[index] = (receivedTime - sendTimes[index]) / 1000.0;
        Serial.printf("Mensaje %d recibido. Latencia: %.6f s\n", index, latencies[index]);
    } else {
        Serial.println("Mensaje fuera de rango recibido.");
    }
}


void setup_wifi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_broker, 1883);
    client.setCallback(callback);
    client.connect("ArduinoClient");
    client.subscribe(topic);
}

void loop() {
    for (int i = 0; i < numMessages; i++) {
        String message = "msg_" + String(i);
        sendTimes[i] = millis();
        client.publish(topic, message.c_str());

        unsigned long startWait = millis();
        while (millis() - startWait < 200) {  // Esperar 200ms procesando MQTT
            client.loop();
        }
    }

    delay(5000);  // Esperar a que lleguen respuestas

    // Calcular latencia promedio
    float sum = 0, sumSq = 0;
    int receivedCount = 0;
    for (int i = 0; i < numMessages; i++) {
        if (latencies[i] > 0) {
            sum += latencies[i];
            sumSq += latencies[i] * latencies[i];
            receivedCount++;
        }
    }

    if (receivedCount > 0) {
        float mean = sum / receivedCount;
        float stddev = sqrt((sumSq / receivedCount) - (mean * mean));
        Serial.printf("Latencia promedio: %.6f s\n", mean);
        Serial.printf("Desviación estándar: %.6f s\n", stddev);
    } else {
        Serial.println("No se recibieron respuestas.");
    }

    while (true);
}