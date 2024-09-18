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
  
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print("V, Dust Density: ");
  Serial.print(dustDensity);
  Serial.println(" mg/m3");

  // Rain Sensor Code
  int rainValue = analogRead(rainSensorPin);  // Read from rain sensor

  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);

  if (rainValue < 300) {
    Serial.println("Heavy rain detected!");
  } else if (rainValue < 700) {
    Serial.println("Light rain detected.");
  } else {
    Serial.println("No rain detected.");
  }

  // DHT11 Sensor Code
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  // MQ-2 Sensor Code
  int sensorValue = analogRead(mq2Pin);  // Read from MQ-2 sensor

  Serial.print("MQ-2 Sensor Value: ");
  Serial.println(sensorValue);
  
  delay(1000);  // Wait for 1 second before next loop
}
