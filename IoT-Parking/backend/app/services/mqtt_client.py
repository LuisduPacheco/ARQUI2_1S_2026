import paho.mqtt.client as paho
from app.db.mongo import parqueos_historial_collection, parqueos_estado_collection
from app.db.config import MQTT_BROKER, MQTT_PORT
from datetime import datetime, timezone

def on_connect(client, userdata, flags, rc):
    print("Conectado a MQTT: ", rc)
    client.subscribe("arqui2/parqueo/1")
    client.subscribe("arqui2/parqueo/2")

def on_message(client, userdata, msg):
    try:
        topic = msg.topic
        payload = msg.payload.decode()

        partes = topic.split("/")
        parqueo_id = partes[-1]

        data = {
            "parqueo_id": parqueo_id,
            "estado": payload,
            "fecha_hora": datetime.now(timezone.utc) 
        }

        parqueos_estado_collection.update_one(
            {"parqueo_id": parqueo_id},
            {"$set": data},
            upsert=True
        )
        # agregar al historial
        parqueos_historial_collection.insert_one(data)

        print(f"Datos del parqueo {parqueo_id} insertados correctamente")
    except Exception as e:
        print(f"Error al insertar datos del parqueo {parqueo_id}")


def start_mqtt():
    cliente = paho.Client()

    cliente.on_connect = on_connect
    cliente.on_message = on_message

    cliente.connect(MQTT_BROKER, int(MQTT_PORT), 60)

    cliente.loop_start()

    print("Se inició el cliente mqtt (suscriber)")
