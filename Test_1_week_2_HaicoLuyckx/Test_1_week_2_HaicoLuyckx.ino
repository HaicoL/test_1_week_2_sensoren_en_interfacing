#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <BH1750.h>

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
BH1750 lightMeter;

#define PIN_LM335 32
#define ADC_VREF_mV 3000.0
#define ADC_RESOLUTION 4096.0

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Wire.begin(D2, D1);
  lightMeter.begin();
}

void loop() {
  float lux = lightMeter.readLightLevel();
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(lux);

  float tempRAW = analogRead(PIN_LM335);
  float volt = tempRAW * 5.0 / 1024;
  float test = volt - 2.73;
  float temperatuur = (test * 100);
  float display = temperatuur / 100;
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(display);
  lcd.print("C");
  Serial.print(display);
  Serial.println("C");
  delay(1000);
}
