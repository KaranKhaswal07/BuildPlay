#include <NewPing.h>

// Pins
const int trigPin = 8;
const int echoPin = 7;
const int maxDistance = 50;  // Maximum distance we want to measure (in cm)

// Initialize NewPing instance
NewPing sonar(trigPin, echoPin, maxDistance);

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor at 9600 baud rate
}

void loop() {
  // Get the distance in cm
  int distance = sonar.ping_cm();
  
  // Print the distance to the serial monitor
  if (distance > 0) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Out of range");
  }
  
  delay(500);  // Wait for 500 milliseconds before the next reading
}
