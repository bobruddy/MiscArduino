

// This is developed for Nolan as a project to setup a monitor for his reptil cage


// **** Prerequisites ****
//
// Adafruit sensor library -> https://github.com/adafruit/Adafruit_Sensor
// Adafruit DHT sensor library -> https://github.com/adafruit/DHT-sensor-library
// Liquid Crystal library -> https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
//
// **** Connections ****
// * GND from Arduino to GND on display
// * GND from Arduino to GND on temp sensor
// * 5V from Arduino to 5V on display
// * 5V from Arduino to 5V on temp sensor
// * 5V from Arduino to resistor ( 10K ohm )
// * resistor to data pin on temp sensor
// * p9 from Arduino to data pin on temp sensor
// * p2 from Arduino to SDA on display
// * p3 from the Ardunio to SCL on display

// power is via the micro-usb port on the ardunio. any USB power will work

// wiring info for the sensor https://learn.adafruit.com/dht/connecting-to-a-dhtxx-sensor
// wiring info for the arduino https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/hardware-overview-pro-micro


#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 9     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7); // you need to get the i2c address with i2c scanner

void setup() {
  // uncomment this for troubleshooting
  //Serial.begin(9600);
  
  dht.begin();
  
  lcd.setBacklightPin( 3, POSITIVE );
  //lcd.setBacklight(LOW);
  lcd.begin( 16,2 );
  lcd.clear();
  
}

void loop() {
  // The DHT11 sensor is a bit slow and can only read new temps every
  // 2 seconds. so don't loop faster than that. There is no reason too
  delay(2000);

  // read the temp and humidify
  float h = dht.readHumidity();
  //float t = dht.readTemperature();      // read temp in C
  float t = dht.readTemperature(true);  // read temp in F

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  It blew up!");
    lcd.setCursor(0,1);
    lcd.print("Can't see sensor");
   
    return;
  }

  // Heat index
  // float hic = dht.computeHeatIndex(f, h);      // heat index in F
  // float hic = dht.computeHeatIndex(t, h, false);  // heat index in C

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.setCursor(10,0);
  lcd.print(h,2);

  lcd.setCursor(0,1);
  lcd.print("Temp *F: ");
  lcd.setCursor(10,1);
  lcd.print(t,2);

  // uncomment these for troubleshooting to the serial monitor
  //Serial.print("Humidity: ");
  //Serial.print(h);
  //Serial.print(" %\t");
  //Serial.print("Temperature: ");
  //Serial.print(t);
  //Serial.print(" *F\n");
 
}
