#include <Keypad.h>
#include <LiquidCrystal.h>


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
const int RS = 12, E = 13, D4 = 0, D5 = 1, D6 = 10, D7 = 11;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

char correctPassword[] = "2812";
char enteredPassword[5];
int passwordIndex = 0;
int attempts = 0;


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
   lcd.begin(16,2);
  //lcd.setCursor(1, 0);       
  lcd.print("Enter password:");    // Display the initial message

}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();     // Read keypress from the keypad

  if (key) {
    lcd.setCursor(passwordIndex, 1);  // Set cursor position for entered password
    lcd.print('*');                  // Display '*' for each keypress

    enteredPassword[passwordIndex] = key;  // Store the entered key
    passwordIndex++;                        // Move to the next position

    if (passwordIndex == 4) {               // Check when 4 digits are entered
      enteredPassword[passwordIndex] = '\0';  // Null-terminate the string
      checkPassword();                        // Call function to check password
      passwordIndex = 0;                      // Reset the index
    }
  }
  


}

void checkPassword() {
  if (strcmp(enteredPassword, correctPassword) == 0) {  // Compare passwords
    lcd.clear();
    lcd.print("Access Granted");  // Display success message
    //digitalWrite(greenLED, HIGH); // Turn on green LED
    delay(2000);
    //digitalWrite(greenLED, LOW);  // Turn off green LED
    lcd.clear();
    lcd.print("Enter Password");  // Prompt for new input
    attempts = 0;                 // Reset the attempts
  } 
  else {
    lcd.clear();
    lcd.print("Access Denied");   // Display failure message
    //digitalWrite(redLED, HIGH);   // Turn on red LED
    delay(2000);
    //digitalWrite(redLED, LOW);    // Turn off red LED
    lcd.clear();
    lcd.print("Enter Password");  // Prompt for new input

    attempts++;                   // Increase the number of failed attempts
    if (attempts >= 3) {          // Check if there have been 3 incorrect attempts
      lcd.clear();
      lcd.print("LOCKED OUT");    // Display lockout message
      //tone(buzzer, 1000);         // Sound the buzzer
      delay(3000);
      //noTone(buzzer);
      attempts = 0;               // Reset attempts after lockout
      lcd.clear();
      lcd.print("Enter Password");
    }
  }
}



