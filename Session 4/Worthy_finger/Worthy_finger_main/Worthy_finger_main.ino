#include <Servo.h>

Servo myServo;
const int buttonPin = 2;  // Pin for push button
const int buzzerPin = 3;  // Pin for buzzer
int numberOfPlayers = 0;
int currentPlayer = 1;
int chosenNumber = 0;
int counter = 0;
bool gameStarted = false;
bool finish=false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Button input with internal pullup
  pinMode(buzzerPin, OUTPUT);        // Buzzer output
  myServo.attach(9);                 // Attach servo to pin 9
  myServo.write(90);                  // Servo starts at position 0 (safe)
  Serial.begin(9600);
  randomSeed(analogRead(0));  // Seed for random number
  Serial.println("\n\n Welcome To the Worthy Finger ");
  Serial.println("\n--- All Player have to press the button one by one and unworthy player's finger will be choped off---\n\n");
  delay(5000);
  Serial.println("Enter the number of players: ");
}

void loop() {
  if (finish) {
    Serial.println("You Finished the Game Use the Magic Reset Button on the Arduino To start again");
  } else {
    if (!gameStarted && Serial.available() > 0) {
      numberOfPlayers = Serial.parseInt();
      if (numberOfPlayers > 1) {
        chosenNumber = random(1, numberOfPlayers + 1);
        gameStarted = true;
      }
      Serial.println("\n \n ------------ 1 out of " + String(numberOfPlayers) + " Player is Worthy. Let's find out who!!! Start Pressing------------- \n");
    }

    if (gameStarted && digitalRead(buttonPin) == LOW) {
      delay(200);  // Debounce
      counter++;


      if (counter == chosenNumber) {
        Serial.println("You Are Not Worthy");
        buzzAndChop();      // Simulate elimination
        eliminatePlayer();  // Reduce the number of players
      } else {
        Serial.println("You Are Safe, Next Person");
        // Move to the next player
        currentPlayer++;
        if (currentPlayer > numberOfPlayers) {
          currentPlayer = 1;
        }
      }
    }
  }
}

void buzzAndChop() {
  digitalWrite(buzzerPin, HIGH);  // Buzzer ON
  myServo.write(0);              // Servo to 90 degrees (chopping action)
  delay(1000);                    // Hold position for 1 second
  digitalWrite(buzzerPin, LOW);   // Buzzer OFF
  myServo.write(90);               // Servo back to 0 degrees
}

void eliminatePlayer() {
  numberOfPlayers--;  // Reduce player count
  counter = 0;        // Reset counter
  
  if (numberOfPlayers > 1) {
    chosenNumber = random(1, numberOfPlayers + 1);  // Choose new number
    Serial.println("\n" + String(numberOfPlayers) + "  Left!!! Start Pressing");
  } else {
    Serial.println("\n\n\n---------------We have a Worthy winner!----------------\n\n\n");
    gameStarted = false;  // End game
    delay(3000);
    finish = true;
  }
}
