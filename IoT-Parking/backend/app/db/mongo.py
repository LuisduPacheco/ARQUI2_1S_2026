from pymongo import MongoClient
from app.db.config import MONGO_DRIVER, MONGODB_USERNAME, MONGODB_PASSWORD, MONGO_HOST, MONGO_PORT, MONGO_DB_NAME

DATABASE_URL = f'{MONGO_DRIVER}://{MONGODB_USERNAME}:{MONGODB_PASSWORD}@{MONGO_HOST}:{MONGO_PORT}/?authSource=admin'

cliente = MongoClient(DATABASE_URL)

db = cliente[MONGO_DB_NAME]

parqueos_historial_collection = db["parqueos"]

parqueos_estado_collection = db["parqueos_estao"]
