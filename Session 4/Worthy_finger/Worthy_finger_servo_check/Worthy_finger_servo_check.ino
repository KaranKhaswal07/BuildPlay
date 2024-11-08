#include <Servo.h>

Servo myServo;  // create a servo object to control the servo
int angle;      // variable to store the angle value

void setup() {
  Serial.begin(9600);    // initialize serial communication at 9600 bps
  myServo.attach(9);     // attach the servo to pin 9
  Serial.println("Enter an angle between 0 and 180:");
}

void loop() {
  if (Serial.available() > 0) {            // check if data is available in the Serial Monitor
    angle = Serial.parseInt();             // read the incoming angle as an integer
    Serial.read();                         // clear any remaining serial data

    if (angle >= 0 && angle <= 180) {      // check if the angle is valid
      myServo.write(angle);                // move the servo to the specified angle
      Serial.print("Servo moved to: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid angle! Enter a value between 0 and 180.");
    }
  }
}
