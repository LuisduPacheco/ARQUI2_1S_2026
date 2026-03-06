#include <WiFi.h>
#include <PubSubClient.h>

// Configurar conexión WIFI
#define WIFI_SSID "Arqui2"
#define WIFI_PASS "arqui226"
#define MQTT_SERVER "10.253.255.70"
#define MQTT_PORT 1883

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// UART Arduino
HardwareSerial SerialUART = Serial2;
const int RXD2 = 16;
const int TXD2 = 17;

String buffer = "";

void setup() {

  Serial.begin(115200);
  SerialUART.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Conectar WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  // Configurar MQTT
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {

  // Conectar MQTT si no está conectado
  if (!mqttClient.connected()) {
    mqttClient.connect("ESP32Parqueo");
  }

  mqttClient.loop();

  // Leer datos desde Arduino
  while (SerialUART.available()) {

    char c = SerialUART.read();

    if (c == '\n') {

      String mensaje = buffer;
      buffer = "";
      mensaje.trim();

      // Extraer espacio1
      int e1 = mensaje.indexOf("\"espacio1\":");
      if (e1 >= 0) {
        int valor = mensaje.substring(e1 + 11, mensaje.indexOf(",", e1)).toInt();
        mqttClient.publish("/parqueo/espacio/uno",
                           valor ? "OCUPADO" : "LIBRE");
      }

      // Extraer espacio2
      int e2 = mensaje.indexOf("\"espacio2\":");
      if (e2 >= 0) {
        int valor = mensaje.substring(e2 + 11, mensaje.indexOf("}", e2)).toInt();
        mqttClient.publish("/parqueo/espacio/dos",
                           valor ? "OCUPADO" : "LIBRE");
      }

    } else {
      buffer += c;
    }
  }
}