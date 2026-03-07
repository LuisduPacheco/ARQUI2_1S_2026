from fastapi import FastAPI
from app.services.mqtt_client import start_mqtt

app = FastAPI()

@app.on_event("startup")
def startup_event():
    start_mqtt()
