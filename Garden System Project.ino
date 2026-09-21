#include <LiquidCrystal_I2C.h>
#include<DHT11.h>

// D3 DHT OUT
// D1 SCL : D2 SDA


DHT11 dht11(D3);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("Smart Gardening");
  lcd.setCursor(5, 1);      
  lcd.print("System");
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  if (result == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature :");
    lcd.setCursor(13,0);
    lcd.print(temperature);
    lcd.setCursor(0,1);
    lcd.print("Humidity");
    lcd.setCursor(12,1);
    lcd.print(":");
    lcd.setCursor(13,1);
    lcd.print(humidity);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("No record is");
    lcd.setCursor(3,1);
    lcd.print("collected");
  }
}