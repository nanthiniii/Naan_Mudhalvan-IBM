//Early Flood Detection Using IOT ~ A project by Sabyasachi Ghosh
//<LiquidCrystal.h> is the library for using the LCD 16x2
#include <LiquidCrystal.h>
//"DHT.h" is the library for using the Temperature sensor DHT22
#include "DHT.h"
#define DHTPIN A0                       //here we are initialising a pin for DHT22
#define DHTTYPE DHT22                   //We have to declare the type of DHT sensor we are using for its correct functionality
LiquidCrystal lcd(2,3,4,5,6,7);         // Create an instance of the LiquidCrystal library
DHT dht(DHTPIN, DHTTYPE);               // Create an instance of the DHT library for the DHT22 sensor
const int in=8;                         //This is the ECHO pin of The Ultrasonic sensor HC-SR04
const int out=9;                        //This is the TRIG pin of the ultrasonic Sensor HC-SR04
// Define pin numbers for various components
const int green=10;
const int orange=11;
const int red=12;
const int buzz=13;

void setup()
{
  // Start serial communication with a baud rate of 9600
  Serial.begin(9600);
  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  // Set pin modes for various components
  pinMode(in, INPUT);
  pinMode(out, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzz, OUTPUT);
  // Initialize the DHT sensor
  dht.begin();
  // Set initial states for LEDs and buzzer to LOW (off)
  digitalWrite(green,LOW);
  digitalWrite(orange,LOW);
  digitalWrite(red,LOW);
  digitalWrite(buzz,LOW);
  // Display a startup message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Flood Monitoring");
  lcd.setCursor(0,1);
  lcd.print("Alerting System");
  // Wait for 5 seconds and then clear the LCD
  delay(5000); 
  lcd.clear();
}

void loop()
{
  // Read temperature and humidity from the DHT22 sensor
  float T = dht.readTemperature();
  float H = dht.readHumidity();
  // Check if the sensor data is valid
  if (isnan(H) && isnan(T)) { 
    lcd.print("ERROR");
    return;
  }
  float f = dht.readTemperature(true);
  // Read distance from the ultrasonic sensor (HC-SR04)
  long dur;
  long dist;
  long per;
  digitalWrite(out,LOW);
  delayMicroseconds(2);
  digitalWrite(out,HIGH);
  delayMicroseconds(10);
  digitalWrite(out,LOW);
  dur=pulseIn(in,HIGH);
  dist=(dur*0.034)/2;
  // Map the distance value to a percentage value
  per=map(dist,10.5,2,0,100);
  // Ensure that the percentage value is within bounds
  if(per<0)
  {
    per=0;
  }
  if(per>100)
  {
    per=100;
  }
  // Print sensor data and percentage value to serial
  Serial.print(("Humidity: "));
  Serial.print(H);
  Serial.print(("%  Temperature: "));
  Serial.print(T);
  Serial.print("%   Water Level:");
  Serial.println(String(per));
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print("Humidity   :");
  lcd.setCursor(12,0);
  lcd.print(T);
  lcd.setCursor(12,1);
  lcd.print(H);
  delay(1000);
  lcd.clear();
  lcd.print("Water Level:");
  lcd.print(String(per));
  lcd.print("%  ");
  // Check water level and set alert levels
  if(dist<=3)
  {
      lcd.setCursor(0,1);
      lcd.print("Red Alert!   ");
      digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
      digitalWrite(orange,LOW);
      digitalWrite(buzz,HIGH);
      delay(2000);
      digitalWrite(buzz,LOW);
      delay(2000);
      digitalWrite(buzz,HIGH);
      delay(2000);
      digitalWrite(buzz,LOW);
      delay(2000);
  }
  else if(dist<=10)
  {
      lcd.setCursor(0,1);
    lcd.print("Orange Alert!  ");
    digitalWrite(orange,HIGH);
    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    digitalWrite(buzz,HIGH);
    delay(3000);
    digitalWrite(buzz,LOW);
    delay(3000);
  }else
  {
     lcd.setCursor(0,1);
    lcd.print("Green Alert!  ");
    digitalWrite(green,HIGH); 
    digitalWrite(orange,LOW);
    digitalWrite(red,LOW);
    digitalWrite(buzz,LOW);
  }
}