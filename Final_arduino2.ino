#include "DHT.h"
#include <LiquidCrystal.h>

// LiquidCrystal(rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(4, 3, 10, 11, 12, 13);
int sensorPin = A5; 
int data;   
int flag = 0;

// Sensor and other hardware Pins
#define DHTPIN 2          // Pin for DHT11
#define DHTTYPE DHT11     // DHT11 sensor type
#define rainSensorPin A1   // Pin for rain sensor
#define dustPin A0         // Pin for dust sensor
#define ledPin 9           // Pin for controlling the LED (from dust sensor)
#define mq2Pin A2          // Pin for MQ-2 sensor
#define piezoPin A3        // Pin for piezo sensor (changed to A3 to avoid conflict)
#define piezoLedPin 8      // Pin for controlling LED with piezo sensor (changed to avoid conflict)
#define threshold 200      // Threshold value for vibration detection

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT11

void setup() {
  // Initialize Serial and Bluetooth communication
  Serial.begin(9600);
  // Sensor setup
  dht.begin();

  pinMode(ledPin, OUTPUT);  // Set LED pin for dust sensor as output
  pinMode(piezoLedPin, OUTPUT);  // Set LED pin for piezo sensor as output
  lcd.begin(16, 2);
  pinMode(sensorPin, INPUT);
  lcd.clear();
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  mobile_detector();

  // Read and print sensor data
  readAndSendSensorData();
}

// Function to read and print sensor data
void readAndSendSensorData() {
  // Dust Sensor Code
  digitalWrite(ledPin, LOW);  
  delayMicroseconds(280);     
  int dustVal = analogRead(dustPin);  // Read from dust sensor pin
  delayMicroseconds(40);
  digitalWrite(ledPin, HIGH);  
  delayMicroseconds(9680);    // Wait before next read

  float voltage = dustVal * (5.0 / 1023.0);  // Convert to voltage
  float dustDensity = 0.17 * voltage - 0.1;  // Convert to dust density

  // Rain Sensor Code
  int rainValue = analogRead(rainSensorPin);  // Read from rain sensor

  // DHT11 Sensor Code
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // MQ-2 Sensor Code
  int mq2Value = analogRead(mq2Pin);  // Read from MQ-2 sensor
  
  // Piezo Sensor Code
  int piezoValue = analogRead(piezoPin);  // Read the analog value from the piezo sensor
  Serial.print("Piezo Value: "); Serial.println(piezoValue);  // Print the piezo sensor value
  
  if (piezoValue > threshold) {
    digitalWrite(piezoLedPin, HIGH);  // Turn on the LED if piezo value is above threshold
  } else {
    digitalWrite(piezoLedPin, LOW);  // Turn off the LED if piezo value is below threshold
  }


  // Send data to Raspberry Pi

  Serial.println("Dust Density: "); Serial.println(dustDensity); 
  Serial.println("Rain Sensor: "); Serial.println(rainValue);
  Serial.println("Humidity: "); Serial.println(humidity);
  Serial.println("Temperature: "); Serial.println(temperature);
  Serial.println("MQ-2: "); Serial.println(mq2Value);
  
  //replace sensor value with battery voltage 
  // Serial.println("Battery: "); Serial.println(sensorValue);
}


void mobile_detector(void)
{
  for (long i = 0; i < 2500; i++)
  {
    data = digitalRead(sensorPin);
    if(data == 1)
    {
      flag = 1; 
    }
  }

  if (flag == 0)
  {
    //Serial.println("No mobile detected: ");
    lcd.clear();  // Clear the screen before displaying new content
    lcd.setCursor(0, 0);  // Set cursor to first line
    lcd.print("No mobile");
    lcd.setCursor(0, 1);  // Set cursor to second line
    lcd.print("detected");
  }
  else
  {
    // Serial.println("Mobile detected: ");
    lcd.clear();  // Clear the screen before displaying new content
    lcd.setCursor(0, 0);  // Set cursor to first line
    lcd.print("Mobile");
    lcd.setCursor(0, 1);  // Set cursor to second line
    lcd.print("detected");
    flag = 0;  // Reset flag for next detection cycle
  }
}