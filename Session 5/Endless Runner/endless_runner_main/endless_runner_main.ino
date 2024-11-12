/*
Welcome To the Endless Runner

Run Run Run.............. watch out the obstical

Author : Karan Khaswal 
Brought to you by : Build&Play Workshop 
Company : Athena Education  
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD setup using I2C at address 0x27 for a 16x2 display

#define PIN_BUTTON 2
#define DEBOUNCE_DELAY 50 // Debounce delay in milliseconds
#define HERO_POS 1        // Position of the hero on the LCD, starting from column 1
#define INITIAL_SPEED 100 // Initial speed (delay between updates)
#define GAP_REDUCTION 5   // Amount by which the gap between obstacles decreases over time
#define MIN_OBSTACLE_GAP 3 // Minimum gap to avoid too many obstacles too quickly

unsigned long lastDebounceTime = 0; // Last time the button was toggled
bool lastButtonState = HIGH;        // the previous reading from the input pin
bool buttonState;                   // the current reading from the input pin
bool gameStarted = false;
int obstaclePosition = 15;          // Start the obstacle at the rightmost side of the LCD
int heroLane = 1;                   // 1 for bottom lane, 0 for top lane
int obstacleLane = 1;               // Lane where the obstacle appears (0 or 1)
int score = 0;                      // Score counter
int speed = INITIAL_SPEED;          // Initial speed (can increase over time)
int obstacleGap = 10;               // Controls the gap between obstacles

void setup() {
    pinMode(PIN_BUTTON, INPUT_PULLUP); // Set up the button pin with an internal pull-up resistor
    lcd.init();                        // Initialize the LCD
    lcd.backlight();                   // Turn on the backlight
    lcd.clear();                       // Clear the LCD screen
    lcd.setCursor(0, 0);
    lcd.print("Press Start");          // Display 'Press Start' on the LCD

    // Initialize randomness using noise from an unused analog pin
    randomSeed(analogRead(A0));
}

void loop() {
    manageButton(); // Call the manageButton function which handles the button press
    if (!gameStarted) {
        return; // If the game hasn't started, do nothing
    }

    lcd.clear();

    // Draw the score on the top right corner (shifted to the end of the screen)
    lcd.setCursor(13, 0);  // Shifting the score to column 13 (end of the LCD)
    lcd.print(score);

    // Draw the hero on the correct lane
    lcd.setCursor(HERO_POS, heroLane);
    lcd.write(byte(1)); // Drawing the hero

    // Draw the obstacle in its lane
    lcd.setCursor(obstaclePosition, obstacleLane);
    lcd.write('#');

    // Move the obstacle to the left
    if (obstaclePosition > 0) {
        obstaclePosition--;
    } else {
        obstaclePosition = 15; // Reset obstacle position after it moves off screen
        obstacleLane = random(0, 2); // Randomly choose a new lane (0 or 1)

        // Increase score when an obstacle successfully passes the hero
        score++;

        // Reduce the gap between obstacles to make the game harder, but maintain a minimum gap
        if (obstacleGap > MIN_OBSTACLE_GAP) {
            obstacleGap -= GAP_REDUCTION;
        }

        // Optionally increase speed as score increases
        speed = max(speed - 5, 50); // Reduce delay over time for faster gameplay
    }

    // Check for collision
    if (obstaclePosition == HERO_POS && obstacleLane == heroLane) {
        gameOver(); // Call gameOver if hero and obstacle collide
    }

    delay(speed); // Adjust for game speed
}

void manageButton() {
    bool reading = digitalRead(PIN_BUTTON);
    // Check if the button state has changed
    if (reading != lastButtonState) {
        lastDebounceTime = millis(); // Reset the debouncing timer
    }
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;
            // Only take action if the button is pressed (LOW due to pullup)
            if (buttonState == LOW) {
                if (!gameStarted) {
                    startGame(); // Start the game if it hasn't started yet
                } else {
                    // Switch the hero lane when button is pressed
                    heroLane = !heroLane; // Toggle between 0 (top) and 1 (bottom) lanes
                }
            }
        }
    }
    lastButtonState = reading; // Save the reading for the next loop iteration
}

void startGame() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game On!");
    gameStarted = true;
    delay(2000); // Display "Game On!" for 2 seconds before clearing the screen
    lcd.clear();
    obstaclePosition = 15;    // Reset obstacle position for game start
    obstacleLane = random(0, 2); // Randomly place obstacle in one of the lanes
    heroLane = 1;             // Start hero in the bottom lane
    score = 0;                // Reset score
    speed = INITIAL_SPEED;    // Reset speed to initial value
    obstacleGap = 10;         // Reset obstacle gap
}

void gameOver() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Over");
    lcd.setCursor(0, 1);
    lcd.print("Final Score:");
    lcd.setCursor(12, 1);
    lcd.print(score);         // Display the final score
    gameStarted = false;
    delay(3000); // Display "Game Over" and final score for 3 seconds
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Start"); // Show start prompt again
}
