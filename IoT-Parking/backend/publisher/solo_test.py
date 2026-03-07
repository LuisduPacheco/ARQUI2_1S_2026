import paho.mqtt.client as mqtt

BROKER: str = "localhost"  # Cambiar por la IP correcta
PORT: int = 1883
TOPIC1: str = "arqui2/parqueo/1"
TOPIC2: str = "arqui2/parqueo/2"

client = mqtt.Client()
client.connect(BROKER, PORT)

stop_mqtt: bool = False

while not stop_mqtt:
    current_status: str = input("Estado Parqueo: ")
    if current_status[0] == "1":
        current_status = current_status[1:]
        client.publish(TOPIC1, current_status)
        print("Topic 1 publicado correctamente")
    elif current_status[0] == "2":
        current_status = current_status[1:]
        client.publish(TOPIC2, current_status)
        print("Topic 2 publicado correctamente")
    else:
        stop_mqtt = True

client.disconnect()