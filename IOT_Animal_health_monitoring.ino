/* 
  Project: IoT Animal Health Monitoring System
  Author : Siddhi Koshti
  MCU    : Arduino Nano
  Sensors: DHT11 (Temperature & Humidity), Pulse Sensor (KY-039 / SEN-11574)
  Display: 16x2 LCD
  Date   : 2025-04-12

  Description:
  This system monitors animal body temperature, humidity level, 
  and approximate heart rate. Useful for livestock health tracking.

  Notes:
  - Open-source prototype for academic demonstration.
  - Includes serial debug logs for calibration and testing.
  - See README for wiring diagram, PCB, demo images, & project workflow.
*/

#include <LiquidCrystal.h>
#include <DHT.h>

// -------------------- Pin Definitions --------------------
#define DHTPIN A0
#define DHTTYPE DHT11
#define PULSE_PIN A1

// -------------------- Objects --------------------
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // RS, EN, D4, D5, D6, D7
DHT dht(DHTPIN, DHTTYPE);

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);

  lcd.print("Health Monitor");
  delay(2000);
  lcd.clear();
}

// -------------------- Main Loop --------------------
void loop() {

  // Read sensor values
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int pulseValue = analogRead(PULSE_PIN);

  // Simple heart rate approximation
  int bpm = map(pulseValue, 0, 1023, 60, 120);  

  // -------------------- LCD Output --------------------
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C H:");
  lcd.print(hum, 1);
  lcd.print("% ");

  lcd.setCursor(0, 1);
  lcd.print("BPM:");
  lcd.print(bpm);

  // -------------------- Serial Debug Output --------------------
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C | Humidity: ");
  Serial.print(hum);
  Serial.print(" % | Heartbeat: ");
  Serial.print(bpm);
  Serial.println(" BPM");

  delay(1000);
}
