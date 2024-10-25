/*
Welcome To the F1 Reflex  
You have to press the button on Choosen Number to score a point
there are 4 Level of the game 
turtle
human 
rabbit
F1

Can you clear all 4 level ? lets find out 

Author : Karan Khaswal 
Brought to you by : Build&Play Workshop 
Company : Athena Education  
*/



// Pin definitions
const int buttonPin = 2;  // Button pin
const int buzzerPin = 3;  // Buzzer pin

// Game variables
int chosenNumber;        // Randomly chosen number
int counter = 0;         // Counter that goes from 1 to 10
bool gameActive = true;  // Game status
int level = 1;           // Start with level 1
int maxLevel = 4;        // Maximum level is 3
bool finish = false;
// Button state
int buttonState;
int lastButtonState = HIGH;  // Start with HIGH for INPUT_PULLUP (button not pressed)
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Timing variables for counter speed
unsigned long previousMillis = 0;
int counterInterval = 1000;  // Start with level 1 speed

void setup() {
  // Initialize the button pin with INPUT_PULLUP
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);

  // Initialize serial for debugging
  Serial.begin(9600);

  // Start the game by choosing a random number between 1 and 10
  randomSeed(analogRead(0));  // Seed for random number
  Serial.println("\n Welcome To the F1 Reflex ");
  Serial.println("\n--- You have to press the button on Choosen Number to score a point---\n\n");
  delay(5000);
  startNewLevel();
}

void loop() {
  if (finish) {
    Serial.println("You Finished the Game Use the Magic Reset Button on the Arduino To start again");
  } else {
    // Set the speed of the counter based on the current level
    if (level == 1) {
      counterInterval = 1000;  // Slow speed (1 second)
    } else if (level == 2) {
      counterInterval = 500;  // Medium speed (0.5 seconds)
    } else if (level == 3) {
      counterInterval = 200;  // Fast speed (0.2 seconds)
    } else if (level == 4) {
      counterInterval = 100;  // Fast speed (0.2 seconds)
    }

    // Update the counter based on the speed
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= counterInterval) {
      previousMillis = currentMillis;
      counter++;
      if (counter > 10) {
        counter = 1;  // Reset counter to 1 after reaching 10
      }
      Serial.println(counter);
    }



    // Debounce the button press
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading == LOW) {  // LOW means the button is pressed with INPUT_PULLUP
        buttonState = LOW;
      } else {
        buttonState = HIGH;
      }
    }

    lastButtonState = reading;

    // Check if the player pressed the button
    if (buttonState == LOW && gameActive) {  // LOW means pressed
      Serial.println("");
      if (counter == chosenNumber) {
        // Player wins, sound the buzzer
        Serial.println("Correct! You win!");
        lastButtonState = HIGH;
        tone(buzzerPin, 1000, 500);  // Play tone for 500ms
        gameActive = false;          // End the current game

        // Move to the next level after a win
        delay(1000);
        Serial.println(" \n \n \n \n");
        increaseLevel();  // Increase the level and restart the game
      } else {
        // Incorrect guess
        Serial.print("Incorrect!           ");
        if (level == 1) {
          Serial.println("Seriously Dude??  Try Again");
        }
        if (level == 2) {
          Serial.println("Cmon Dude its just level 2 !!   Try Again");
        }
        if (level == 3) {
          Serial.println("Cmon its not that fast!!  Try Again");
        }
        if (level == 4) {
          Serial.println("Thats the Boss Level Cmon!!!!   Try Again");
        }

        tone(buzzerPin, 800, 200);
        counter = 0;
        Serial.print("Chosen number: ");
        Serial.println(chosenNumber);
        lastButtonState = HIGH;
        delay(3000);
        Serial.println(" \n \n \n \n");
        timer();
      }
    }
  }
}

void startNewLevel() {
  // Reset the game logic and start a new level
  chosenNumber = random(1, 11);  // Choose a new random number
  Serial.print("Level ");
  Serial.print(level);
  if (level == 1) {
    Serial.print(" Turtle  ");
  }
  if (level == 2) {
    Serial.print(" Human  ");
  }
  if (level == 3) {
    Serial.print(" Rabbit  ");
  }
  if (level == 4) {
    Serial.print(" F1  ");
  }

  Serial.print(", Chosen number: ");
  Serial.println(chosenNumber);
  Serial.println("");
  timer();
  Serial.println(" \n \n");
  counter = 0;        // Reset the counter to 1
  gameActive = true;  // Activate the game
}

void timer() {
  Serial.print("Ready ");
  delay(2000);
  Serial.print("Set ");
  delay(2000);
  Serial.print("Go !");
  delay(300);
  Serial.println(" \n \n");
}
void increaseLevel() {
  // Increase the level up to the maximum level
  if (level < maxLevel) {
    level++;
    startNewLevel();
  } else {
    finish = true;
  }
}
