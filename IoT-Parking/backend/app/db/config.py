from dotenv import load_dotenv
import os

load_dotenv()

MONGODB_USERNAME: str = os.getenv("MONGODB_USERNAME")
MONGODB_PASSWORD: str = os.getenv("MONGODB_PASSWORD")
MONGO_PORT: int = os.getenv("MONGO_PORT")
MQTT_PORT: int = os.getenv("MQTT_PORT")
MQTT_WBS: int = os.getenv("MQTT_WBS")
MQTT_BROKER: str = os.getenv("MQTT_BROKER")
MONGO_PORT=27017
MONGO_DB_NAME: str = os.getenv("MONGODB_USERNAME")
MONGO_DRIVER: str = os.getenv("MONGO_DRIVER")
MONGO_HOST: str = os.getenv("MONGO_HOST")
JWT_SECRET_KEY: str = os.getenv("JWT_SECRET_KEY")
JWT_ALGORITHM: str = os.getenv("JWT_ALGORITHM")
ACCESS_TOKEN_EXPIRE_MINUTES: str = os.getenv("ACCESS_TOKEN_EXPIRE_MINUTES")