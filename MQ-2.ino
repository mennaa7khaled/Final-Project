int mq2Pin = A0;  
int sensorValue = 0;

void setup() {
  Serial.begin(9600);  // Initialize serial communication at a baud rate of 9600
}

void loop() {
  // Read the analog value from the MQ-2 sensor
  sensorValue = analogRead(mq2Pin);
  
  // Print the analog value to the Serial Monitor
  Serial.print("MQ-2 Sensor Value: ");
  Serial.println(sensorValue);
  
  // Add a delay to avoid flooding the serial output
  delay(1000);  // 1 second delay between readings
}
