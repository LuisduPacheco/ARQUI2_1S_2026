#include <LiquidCrystal_I2C.h>

# La dirección puede cambiar, 0x27 o 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int botonEspacio1 = 2;
const int botonEspacio2 = 3;

bool espacioOcupado1 = false;
bool espacioOcupado2 = false;


void setup(){
  
# INPUT_PULLUP porque no usa resistencias externas, usa las internas de Arduino
  pinMode(botonEspacio1, INPUT_PULLUP);
  pinMode(botonEspacio2, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
# El cursor siempre se posiciona antes de escribir con print()
  lcd.setCursor(0, 0);
  lcd.print("Parqueo Arqui2");
  delay(300);
}

void loop(){
  bool nuevoEspacio1 = (digitalRead(botonEspacio1) == LOW);
  bool nuevoEspacio2 = (digitalRead(botonEspacio2) == LOW);

  if(nuevoEspacio1 != espacioOcupado1 || nuevoEspacio2 != espacioOcupado2){
    espacioOcupado1 = nuevoEspacio1;
    espacioOcupado2 = nuevoEspacio2;
    lcd.clear();
    lcd.setCursor(0, 0);
    if (espacioOcupado1 && espacioOcupado2) {
      lcd.print("Parqueo lleno");
    } else {
      lcd.print("Parqueo libre");
    }
    lcd.setCursor(0,1);
    if (espacioOcupado1) {
      lcd.print("OC1 ");
    } else {
      lcd.print("LIB1 ");
    }

    lcd.print(espacioOcupado2 ? "OC2 " : "LIB2 ");
  }
  delay(150);
}
