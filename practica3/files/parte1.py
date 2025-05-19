import paho.mqtt.client as mqtt
import time
import numpy as np
import matplotlib.pyplot as plt
                                                                                                                                                                       
# Configuración del broker MQTT
BROKER = "test.mosquitto.org"  # Puedes cambiarlo por tu brok
TOPIC = "elementos2/Hector"
NUM_MESSAGES = 10000  # Ajustado a 10000 para coincidir con la imagen
times = []  # Lista para almacenar los tiempos de ida y vuelta
sent_times = {}  # Diccionario para almacenar los tiempos de envío

def on_connect(client, userdata, flags, rc):
    print("Conectado al broker MQTT con código de resultado:", rc)
    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    global times
    receive_time = time.time()
    msg_id = int(msg.payload.decode())
    if msg_id in sent_times:
        round_trip_time = receive_time - sent_times[msg_id]
        times.append(round_trip_time)
        del sent_times[msg_id]  # Remover mensaje procesado

def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(BROKER, 1883, 60)
    client.loop_start()
    
    print("Enviando mensajes...")
    for i in range(NUM_MESSAGES):
        sent_times[i] = time.time()
        client.publish(TOPIC, str(i))
        time.sleep(0.005)  # Reducida la pausa para más mensajes
    
    time.sleep(5)  # Esperar a recibir respuestas
    client.loop_stop()
    client.disconnect()
    
    if times:
        promedio = np.mean(times)
        desviacion = np.std(times)
        
        plt.figure(figsize=(10, 6))
        plt.scatter(range(len(times)), times, color='blue', s=1, alpha=0.6, label="Latency (s)")
        plt.axhline(promedio, color='green', linestyle='dashed', label=f'Mean = {promedio:.4f} s')
        plt.axhline(promedio + desviacion, color='orange', linestyle='dashed', label=f'+1 Std Dev = {promedio + desviacion:.4f} s')
        plt.axhline(promedio - desviacion, color='red', linestyle='dashed', label=f'-1 Std Dev = {promedio - desviacion:.4f} s')
        
        plt.xlabel("Message Index")
        plt.ylabel("Δt (s)")
        plt.title("MQTT Message Latency")
        plt.legend()
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.show()
    else:
        print("No se recibieron respuestas.")

if __name__ == "__main__":
    main()