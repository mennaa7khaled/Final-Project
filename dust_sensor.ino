const int dustPin = A0;  
const int ledPin = 9;    

void setup() {
  Serial.begin(9600);    
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  digitalWrite(ledPin, LOW);  
  delayMicroseconds(280);     
  
  int dustVal = analogRead(dustPin);  
  
  delayMicroseconds(40);
  digitalWrite(ledPin, HIGH);  
  
  delayMicroseconds(9680);   

  float voltage = dustVal * (5.0 / 1023.0);
  float dustDensity = 0.17 * voltage - 0.1;
  
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print("V, Dust Density: ");
  Serial.print(dustDensity);
  Serial.println(" mg/m3");

  delay(1000);
}
