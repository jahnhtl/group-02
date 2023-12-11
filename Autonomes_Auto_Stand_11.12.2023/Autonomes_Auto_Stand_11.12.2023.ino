#define Button 2
#define EmergencyButton 1 // Defining the emergency button pin
#define SharpSensorLeft A0 // Pin for left Sharp sensor
#define SharpSensorRight A1 // Pin for right Sharp sensor
#define ThresholdDistance 15 // Threshold distance to detect obstacles (adjust as needed)

int ButtonState = 0;
int EmergencyButtonState = 0;
int buttonPressed = 0; // Variable to track if the regular button has been pressed

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(EmergencyButton, INPUT_PULLUP); // Set emergency button pin as input with pull-up resistor
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(SharpSensorLeft, INPUT);
  pinMode(SharpSensorRight, INPUT);
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

  // Obstacle detection using Sharp sensors
  float distanceLeft = analogRead(SharpSensorLeft);
  float distanceRight = analogRead(SharpSensorRight);

  // Convert analog readings to distance in centimeters
  distanceLeft = 27.86 * pow(distanceLeft, -1.15); // Formula for GP2Y0A21YK sensor
  distanceRight = 27.86 * pow(distanceRight, -1.15); // Formula for GP2Y0A21YK sensor

  // Check left sensor for obstacle
  if (distanceLeft < ThresholdDistance) {
    // Perform left side avoidance action here
    // For example, adjust motor or change direction to avoid obstacle on the left
    // Add your code here for left side avoidance
  }

  // Check right sensor for obstacle
  if (distanceRight < ThresholdDistance) {
    // Perform right side avoidance action here
    // For example, adjust motor or change direction to avoid obstacle on the right
    // Add your code here for right side avoidance
  }
}




                                                                                                                                                                                                                                                                                                                                                                                                                           
