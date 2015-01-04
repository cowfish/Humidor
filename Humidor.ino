/*
Humidor manager

Shows current temp and humidity of a sensor

Todo: add button to trigger a spot reading
Todo: make button press switch on LCD for a short time

*/

#include <LiquidCrystal.h>
#include <dht.h>

#define dht_dpin 8 // DHT11 sensor pin
dht DHT;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // start the Ethernet connection and the server:
  lcd.begin(16, 2);
  lcd.clear();
}

long lastCheck=0;
#define CHECKINTERVAL 10000 // ms of check interval

int temperature=0;
int humidity=0;
char tick='-';

void loop() {
  long now=millis();
  if (now-lastCheck>CHECKINTERVAL) {
    DHT.read11(dht_dpin);
    temperature=DHT.temperature;
    humidity=DHT.humidity;
    lastCheck=now;
        
    lcd.print("Temperature: ");
    lcd.print(temperature);
    lcd.print("C");
    
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
    
    lcd.setCursor(15,1);
    lcd.write(tick);
    tick=tick=='-'?'|':'-';
  }      
}

