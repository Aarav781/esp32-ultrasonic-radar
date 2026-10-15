#include <ESP32Servo.h>

// Pin Definitions
const int trigPin = 12;  
const int echoPin = 14;  
const int servoPin = 13; 

long duration;
int distance;

Servo myServo; 

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  
  Serial.begin(115200); 
  
  // ESP32 Servo setup
  myServo.setPeriodHertz(50); 
  myServo.attach(servoPin, 500, 2400); 
}

void loop() {
  // Sweep from 15 to 165 degrees
  for(int i=15; i<=165; i++){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    
    sendData(i, distance);
  }
  
  // Sweep back from 165 to 15 degrees
  for(int i=165; i>15; i--){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    
    sendData(i, distance);
  }
}

// Function to calculate distance via Ultrasonic Sensor
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // pulseIn returns the duration in microseconds
  duration = pulseIn(echoPin, HIGH); 
  
  // Speed of sound is 0.034 cm/us
  distance = duration * 0.034 / 2;
  return distance;
}

// Function to format serial output for Processing/Visualizers
void sendData(int angle, int dist) {
  Serial.print(angle); 
  Serial.print(","); 
  Serial.print(dist); 
  Serial.print("."); 
}