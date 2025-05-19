import time
import paho.mqtt.client as mqtt
# Configuración de MQTT
mqtt_broker = 'test.mosquitto.org'
topic = 'elementos2/hecojeda/'
# MQTT Client
client = None
def on_connect(client, userdata, flags, rc):
    print(f"Conectado con código de resultado {rc}")
    client.subscribe(topic)
def on_message(client, userdata, msg):
    print(f"Mensaje recibido en el tema {msg.topic}: {msg.payload.decode()}")
def send_message(message):
    """Envía un mensaje al broker MQTT"""
    client.publish(topic, message)
    print(f"Mensaje '{message}' enviado")
def main():
    global client
    # Configuración del cliente MQTT
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    # Conectar al broker MQTT
    client.connect(mqtt_broker, 1883, 60)
    client.loop_start()
    print("Esperando que escribas un mensaje para enviarlo...")
    while True:
        # Espera a que el usuario escriba un mensaje
        message = input("Escribe un mensaje para enviar (o 'exit' para salir): ")
        if message.lower() == 'exit':
            print("Saliendo del programa...")
            break
        send_message(message)
        time.sleep(1)
if __name__ == "__main__":
    main()
 