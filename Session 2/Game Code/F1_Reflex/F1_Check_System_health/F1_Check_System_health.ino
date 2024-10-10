// Pin definitions
const int buttonPin = 2;   // Button connected to pin 2
const int buzzerPin = 3;   // Buzzer connected to pin 3

void setup() {
  // Initialize the button pin as an input with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Initialize the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the button state (LOW when pressed, HIGH when not pressed due to INPUT_PULLUP)
  int buttonState = digitalRead(buttonPin);

  // Check if the button is pressed (LOW means pressed)
  if (buttonState == LOW) {
    // If the button is pressed, turn on the buzzer
    tone(buzzerPin, 1000);  // Play a 1000Hz tone
    Serial.println("Button Pressed! Buzzer ON");
  } else {
    // If the button is not pressed, turn off the buzzer
    noTone(buzzerPin);  // Stop the buzzer
    Serial.println("Button not pressed. Buzzer OFF");
  }

  delay(100);  // Small delay to avoid spamming the serial monitor
}
