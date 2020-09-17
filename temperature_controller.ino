#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2
#define VALVE_PIN 3
#define MIN_TEMP 30
#define MAX_TEMP 35
         
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress first_thermometer, second_thermometer;

void setup() {
  pinMode(VALVE_PIN, OUTPUT);
  digitalWrite(VALVE_PIN, LOW);
  lcd.init();
  lcd.backlight();
  sensors.begin();
  sensors.getAddress(first_thermometer,0);
  sensors.getAddress(second_thermometer,1);
  sensors.setResolution(second_thermometer,12);
  sensors.setResolution(first_thermometer, 12);
}


void loop() {
 
  sensors.requestTemperatures();
  float temp1 = sensors.getTempC(first_thermometer);
  float temp2 = sensors.getTempC(second_thermometer);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T1: ");
  lcd.print(temp1);
  lcd.print(" C");
  if (temp1 > MIN_TEMP && temp1 < MAX_TEMP)
  {
    digitalWrite(VALVE_PIN, HIGH);
  }
  else
  {
    digitalWrite(VALVE_PIN, LOW);
  }
  lcd.setCursor(0,1);
  lcd.print("T2: ");
  lcd.print(temp2);
  lcd.print(" C");
  delay(1000);
}
