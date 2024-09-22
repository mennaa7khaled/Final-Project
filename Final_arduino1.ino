#include <SoftwareSerial.h>

// Bluetooth communication pins
SoftwareSerial Bluetooth(4, 5);

// Motor Control Pins
#define IN1 10
#define IN2 11
#define IN3 12
#define IN4 13

char Reading;

void setup() {
  // Initialize Serial and Bluetooth communication
  Serial.begin(9600);
  Bluetooth.begin(9600);
  
  // Motor control setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Check for Bluetooth input
  if (Bluetooth.available() > 0) {
    Reading = Bluetooth.read();
    // Serial.print("Received command: ");
    // Serial.println(Reading);

    // Control motors based on Bluetooth input
    switch (Reading) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'R': right(); break;
      case 'L': left(); break;
      case 'S': stopp(); break;
    }
  }
}


// Motor control functions
void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
  Serial.println("Moving forward");
}

void backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);  
  Serial.println("Moving backward");
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);  
  Serial.println("Turning left");
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  Serial.println("Turning right");
}

void stopp() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);
  Serial.println("Stopped");
}
