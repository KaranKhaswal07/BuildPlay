#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27 and 16 columns x 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
  // Clear the screen
  lcd.clear();
  
  // Display a welcome message
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("Hello, World!");
}

void loop() {
  static int counter = 0;
  
  // Set the cursor to the beginning of the second row
  lcd.setCursor(0, 1);
  // Print the counter value
  lcd.print("Count: ");
  lcd.print(counter);
  
  // Increment the counter and wrap back to 0 after 100
  counter = (counter + 1) % 100;
  
  // Delay for 1 second
  delay(1000);
}
