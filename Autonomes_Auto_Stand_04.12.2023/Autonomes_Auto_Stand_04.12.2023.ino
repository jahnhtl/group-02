#define Button 2
#define EmergencyButton 1 // Defining the emergency button pin

int ButtonState = 0;
int EmergencyButtonState = 0;
int buttonPressed = 0; // Variable to track if the regular button has been pressed

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(EmergencyButton, INPUT_PULLUP); // Set emergency button pin as input with pull-up resistor
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  ButtonState = digitalRead(Button);
  EmergencyButtonState = digitalRead(EmergencyButton);

  // Check if the regular button is pressed and it hasn't been pressed before
  if (ButtonState == LOW && buttonPressed == 0) {
    digitalWrite(6, HIGH); // Turn on LED connected to pin 6
    digitalWrite(5, HIGH); // Turn on LED connected to pin 5
    buttonPressed = 1; // Set buttonPressed to 1 to indicate the regular button has been pressed
  }

  // Check emergency button for an emergency situation
  if (EmergencyButtonState == LOW) {
    // Perform emergency shutdown or action here
    digitalWrite(6, LOW); // Turn off LED connected to pin 6
    digitalWrite(5, LOW); // Turn off LED connected to pin 5
    buttonPressed = 0; // Reset buttonPressed to allow regular button functionality again
  }
}

/*
#define Button 2
int ButtonState = 0;
int buttonPressed = 0; // Variable to track if the button has been pressed

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  ButtonState = digitalRead(Button);

  // Check if the button is pressed and it hasn't been pressed before
  if (ButtonState == LOW && buttonPressed == 0) {
    digitalWrite(6, HIGH); // Turn on LED connected to pin 6
    digitalWrite(5, HIGH); // Turn on LED connected to pin 5
    buttonPressed = 1; // Set buttonPressed to 1 to indicate the button has been pressed
  }
}
 */
