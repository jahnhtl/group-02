#define Button 2
#define EmergencyButton 1 // Defining the emergency button pin
#define SharpSensorLeft A0 // Pin for left Sharp sensor
#define SharpSensorRight A1 // Pin for right Sharp sensor
#define SharpSensorMiddle A2 // Pin for middle Sharp sensor
#define ThresholdDistance 15 // Threshold distance to detect obstacles (adjust as needed)
#define MotorLeft 6 // Pin for left motor
#define MotorRight 5 // Pin for right motor
#define MotorSpeedForward 255 // Motor speed for forward movement
#define MotorSpeedReverse 150 // Motor speed for reverse movement

int ButtonState = 0;
int LastButtonState = HIGH; // Variable to store the last state of the regular button
int EmergencyButtonState = 0;
bool buttonPressed = false; // Variable to track if the regular button has been pressed

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(EmergencyButton, INPUT_PULLUP); // Set emergency button pin as input with pull-up resistor
  pinMode(MotorLeft, OUTPUT);
  pinMode(MotorRight, OUTPUT);
  pinMode(SharpSensorLeft, INPUT);
  pinMode(SharpSensorRight, INPUT);
  pinMode(SharpSensorMiddle, INPUT);

  Serial.begin(9600); // Start serial communication
}

void loop() {
  ButtonState = digitalRead(Button);
  EmergencyButtonState = digitalRead(EmergencyButton);

  if (ButtonState == LOW && LastButtonState == HIGH) {
    // Regular button pressed
    buttonPressed = !buttonPressed;
    LastButtonState = LOW;
  } else if (ButtonState == HIGH) {
    LastButtonState = HIGH;
  }

  if (buttonPressed) {
    // Regular button action when pressed
    Serial.println("Regular Button Pressed");
    // Perform desired actions here when the regular button is pressed
  }

  if (EmergencyButtonState == LOW) {
    // Emergency button action when pressed
    Serial.println("Emergency Button Pressed");
    // Perform emergency actions here when the emergency button is pressed
  }

  // Obstacle detection using Sharp sensors
  float distanceLeft = analogRead(SharpSensorLeft);
  float distanceRight = analogRead(SharpSensorRight);
  float distanceMiddle = analogRead(SharpSensorMiddle);

  // Convert analog readings to distance in centimeters
  distanceLeft = 27.86 * pow(distanceLeft, -1.15); // Formula for GP2Y0A21YK sensor
  distanceRight = 27.86 * pow(distanceRight, -1.15); // Formula for GP2Y0A21YK sensor
  distanceMiddle = 27.86 * pow(distanceMiddle, -1.15); // Formula for GP2Y0A21YK sensor

  // Motor speed variables
  int leftSpeed = MotorSpeedForward;
  int rightSpeed = MotorSpeedForward;

  // Adjust motor speeds based on sensor readings
  if (distanceLeft < ThresholdDistance && distanceRight < ThresholdDistance) {
    // If both left and right sensors detect obstacle, move to a free direction
    // Here, you can implement a logic to move the robot in a free direction
    // For example, stop motors or perform a turn
    // Add your code here for free movement when both sensors detect obstacles
    leftSpeed = 0;
    rightSpeed = 0;
  } else if (distanceMiddle < ThresholdDistance) {
    // If the middle sensor detects an obstacle, move backwards
    leftSpeed = -MotorSpeedReverse; // Reverse left motor
    rightSpeed = -MotorSpeedReverse; // Reverse right motor
  } else {
    // No obstacle detected, move forward
    // Set motor speeds for forward movement
    leftSpeed = MotorSpeedForward;
    rightSpeed = MotorSpeedForward;
  }

  // Set motor speeds using analogWrite()
  analogWrite(MotorLeft, abs(leftSpeed)); // Make sure speed is positive
  analogWrite(MotorRight, abs(rightSpeed)); // Make sure speed is positive
}
