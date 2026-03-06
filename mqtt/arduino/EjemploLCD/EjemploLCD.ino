#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// -------- LCD --------
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// -------- Pines --------
const int botonEspacio1 = 2;
const int botonEspacio2 = 3;

// UART hacia ESP32
#define RX_ESP 10
#define TX_ESP 11
SoftwareSerial espSerial(RX_ESP, TX_ESP);

// -------- Variables --------
bool espacioOcupado1 = false;
bool espacioOcupado2 = false;

void setup(){

  pinMode(botonEspacio1, INPUT_PULLUP);
  pinMode(botonEspacio2, INPUT_PULLUP);

  Serial.begin(9600);
  espSerial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parqueo Arqui2");
  delay(1000);
}

void loop(){

  bool nuevoEspacio1 = (digitalRead(botonEspacio1) == LOW);
  bool nuevoEspacio2 = (digitalRead(botonEspacio2) == LOW);

  if(nuevoEspacio1 != espacioOcupado1 || nuevoEspacio2 != espacioOcupado2){

    espacioOcupado1 = nuevoEspacio1;
    espacioOcupado2 = nuevoEspacio2;

    // -------- LCD --------
    lcd.clear();
    lcd.setCursor(0, 0);

    if (espacioOcupado1 && espacioOcupado2) {
      lcd.print("Parqueo lleno");
    } else {
      lcd.print("Parqueo libre");
    }

    lcd.setCursor(0,1);
    lcd.print(espacioOcupado1 ? "OC1 " : "LIB1 ");
    lcd.print(espacioOcupado2 ? "OC2 " : "LIB2 ");

    // -------- Enviar JSON al ESP32 --------
    String datos = "{\"espacio1\":" + String(espacioOcupado1 ? 1 : 0) +
                   ",\"espacio2\":" + String(espacioOcupado2 ? 1 : 0) + "}\n";

    espSerial.print(datos);
    Serial.println("Enviado -> " + datos);
  }

  delay(150);
}