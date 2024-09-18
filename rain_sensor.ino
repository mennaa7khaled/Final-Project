int rainSensorPin = A0;
int rainValue = 0;  

void setup() {
  Serial.begin(9600);
}

void loop() {
  rainValue = analogRead(rainSensorPin);

  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);

  if (rainValue < 300) {
    Serial.println("Heavy rain detected!");
  } else if (rainValue < 700) {
    Serial.println("Light rain detected.");
  } else {
    Serial.println("No rain detected.");
  }

  delay(1000);
}
