const int piezoPin = A2; // Pin connected to the piezo sensor
const int ledPin = 2;   // Pin connected to the LED
const int threshold = 200; // Threshold value for vibration detection

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void loop() {
  int sensorValue = analogRead(piezoPin); // Read the analog value from the piezo sensor
  Serial.println(sensorValue); // Print the sensor value to the Serial Monitor
  
  if (sensorValue > threshold) {
    digitalWrite(ledPin, HIGH); // Turn on the LED if the sensor value is above the threshold
  } else {
    digitalWrite(ledPin, LOW); // Turn off the LED if the sensor value is below the threshold
  }
  
  delay(100); // Delay for a short period to avoid flooding the Serial Monitor
}
