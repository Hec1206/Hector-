import paho.mqtt.client as mqtt

# Configuración del broker y canal
mqtt_broker = "test.mosquitto.org"
topic = "elementos2/augusto"

# Callback cuando se conecta al broker
def on_connect(client, userdata, flags, rc):
    print(f"Conectado al broker MQTT con código {rc}")
    client.subscribe(topic)
    print(f"Suscrito al canal: {topic}")

# Callback cuando se recibe un mensaje
def on_message(client, userdata, msg):
    print(f"Valor recibido del potenciómetro: {msg.payload.decode()}")

# Crear cliente MQTT
client = mqtt.Client()

# Asignar callbacks
client.on_connect = on_connect
client.on_message = on_message

# Conectar al broker
client.connect(mqtt_broker, 1883, 60)

# Iniciar loop
print("Esperando datos del ESP32...")
client.loop_forever()