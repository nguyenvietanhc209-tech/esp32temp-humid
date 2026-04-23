#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 4     
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);
// set the LCD number of columns and rows
int lcdColumns = 38;
int lcdRows = 4;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
void setup() {
  Serial.begin(115200); // Initialize the serial communication at a baud rate of 115200
  dht.begin();
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}
void loop() {
  lcd.clear();
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print(F("Humidity: "));
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print(F("Temperature:"));
  lcd.print(t);
  delay(2000);
}