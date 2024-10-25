/*
Welcome To the Distance Master
You have to Gussed the correct distance by putting your hand away from the Ultrasonic Sensor
there are 5 level of points 

Bullseye! +10 points        (Perfect Guess)
Bravo! +5 points            (Missed by 3 cm)
Not Bad! +3 points          (Missed by 6 cm)
Poor! +1 point              (Missed by 10 cm)
Bro Seriously! 0 point      (Missed by 20 cm)

You will get 10 chance

Can you get 100/100
lets find out!!!!

Author : Karan Khaswal 
Brought to you by : Build&Play Workshop 
Company : Athena Education  
*/



#include <NewPing.h>

// Pins
const int trigPin = 8;
const int echoPin = 7;
const int buzzerPin = 3;
const int maxDistance = 50;  // Maximum range of 50 cm

// Variables
int distance;
int targetDistance = 0;
int score = 0;
int attempts = 0;
const int maxAttempts = 10;                    // Maximum attempts for the player
NewPing sonar(trigPin, echoPin, maxDistance);  // Initialize NewPing

void setup() {
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(A0));  // Seed the random generator using analog noise
  Serial.println("\n Welcome To the Distance Master ");
  Serial.println("\n--- You have to Gussed the correct distance by putting your hand away from the Ultrasonic Sensor---\n\n");
  delay(5000);
  Serial.println("\n--- Get offset value before the game (hint : Check for 10cm and 50cm )---\n\n");
  delay(1000);
  timer();
  for(int i=0;i<70;i++){
    distance = getStableDistance();  // Get a stable distance using NewPin
    // Display the measured distance
    Serial.print("Your Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(200);
  }
  Serial.println("\n\n\n\n\n");
  Serial.println("\n--- Let Start The Match You have 10 chance,     Be precise---\n\n");
  delay(2000);
  startNewRound();  // Begin the game by selecting a random distance

}

void loop() {
  if (attempts < maxAttempts) {
    distance = getStableDistance();  // Get a stable distance using NewPing

    // Display the measured distance
    Serial.print("Your Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Check how close the player's distance is to the target distance
    int difference = abs(distance - targetDistance);
    if (difference == 0) {
      Serial.println("Bullseye! +10 points");
      score += 10;
      delay(1000);
    } else if (difference <= 3) {
      Serial.println("Bravo! +5 points");
      score += 5;
      delay(1000);
    } else if (difference <= 6) {
      Serial.println("Not Bad! +3 points");
      score += 3;
      delay(1000);
    } else if (difference <= 10) {
      Serial.println("Poor! +1 point");
      score += 1;
      delay(1000);
    } else if(difference <= 20 ){
      Serial.println("Bro Seriously! 0 point");
      delay(1000);
    }
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);

    attempts++;
    delay(2000);  // Wait before the next attempt
    if (attempts < maxAttempts) {
      startNewRound();  // Start a new round with a new target distance
    }
  } else {
    Serial.print("\n\n Game Over! Your total score is: ");
    Serial.print(score);
    Serial.println("/100");
    while (true)
      ;  // Stop the loop
  }
}

void startNewRound() {
  // Choose a new target distance divisible by 5 between 10 and 50
  Serial.println("\n" + String(attempts + 1) + " Attempt!!");
    targetDistance = random(2, 11) * 5;
  Serial.println("\nKeep your hand " + String(targetDistance) + " cm away!!");
  timer();
}

void timer() {
  Serial.print("Ready ");
  delay(2000);
  Serial.print("Set ");
  delay(2000);
  Serial.print("Go!");
  delay(300);
  Serial.println(" \n \n");
}

int getStableDistance() {
  // Discard a few initial readings for better accuracy
  // for (int i = 0; i < 5; i++) {
  //   sonar.ping_cm();  // Initial readings discarded
  // }
  // Return the stabilized distance
  return sonar.ping_cm();
}
