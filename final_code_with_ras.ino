#include "DHT.h"

#define DHTPIN 2          // Pin for DHT11
#define DHTTYPE DHT11     // DHT11 sensor type
#define rainSensorPin A1   // Pin for rain sensor
#define dustPin A0         // Pin for dust sensor
#define ledPin 9           // Pin for controlling the LED
#define mq2Pin A2          // Pin for MQ-2 sensor

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT11

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
}

void loop() {
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
  int sensorValue = analogRead(mq2Pin);  // Read from MQ-2 sensor
  
  // Send data to Raspberry Pi
  Serial.print("Voltage: "); Serial.print(voltage); Serial.print("V, ");
  Serial.print("Dust Density: "); Serial.print(dustDensity); Serial.print(" mg/m3, ");
  Serial.print("Rain Sensor: "); Serial.print(rainValue); Serial.print(", ");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.print("%, ");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.print("°C, ");
  Serial.print("MQ-2: "); Serial.println(sensorValue);

  delay(1000);  // Wait for 1 second before next loop
}
