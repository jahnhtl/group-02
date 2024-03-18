#define Button 2
#define EmergencyButton 1
#define SharpSensorLeft A0
#define SharpSensorRight A1
#define ThresholdDistance A5

// Motor Pins
#define LEFT_MOTOR_PIN 5
#define RIGHT_MOTOR_PIN 6

int ButtonState = 0;
int EmergencyButtonState = 0;
int buttonPressed = 0;

int leftSpeed = 255;  // Geschwindigkeit für linken Motor (0-255)
int rightSpeed = 255; // Geschwindigkeit für rechten Motor (0-255)

float convertedDistanceRight;
float convertedDistanceLeft;
float convertedDistanceForward;

const float Mittelposition = 50; // Annahme einer mittigen Position (kann je nach Fahrzeug variieren)
const float Toleranz = 5;

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(EmergencyButton, INPUT_PULLUP);
  pinMode(SharpSensorLeft, INPUT);
  pinMode(SharpSensorRight, INPUT);
  pinMode(ThresholdDistance, INPUT);
  
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void convertToCentimetersRight(int rawValue) {
   convertedDistanceRight = (uint16_t) (6000 / (rawValue - 6.89)) - 4;
   convertedDistanceRight = constrain(convertedDistanceRight, 9, 81);
}

void convertToCentimetersLeft(int rawValue) {
   convertedDistanceLeft = (uint16_t) (6000 / (rawValue - 6.89)) - 4;
   convertedDistanceLeft = constrain(convertedDistanceLeft, 9, 81);
}

void convertToCentimetersForward(int rawValue) {
   convertedDistanceForward = (uint16_t) (16256 / (rawValue + 22.8)) - 8;
   convertedDistanceForward = constrain(convertedDistanceForward, 19, 151);
}

void Mittenregelung() {
  if (convertedDistanceLeft > convertedDistanceRight + Toleranz) {
    analogWrite(LEFT_MOTOR_PIN, leftSpeed / 2);
    analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
  } else if (convertedDistanceRight > convertedDistanceLeft + Toleranz) {
    analogWrite(LEFT_MOTOR_PIN, leftSpeed);
    analogWrite(RIGHT_MOTOR_PIN, rightSpeed / 2);
  } else {
    analogWrite(LEFT_MOTOR_PIN, leftSpeed);
    analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
  }
}

void loop() {
    ButtonState = digitalRead(Button);
    EmergencyButtonState = digitalRead(EmergencyButton);

    if (ButtonState == LOW && buttonPressed == 0) {
      buttonPressed = 1;
    }

    if (EmergencyButtonState == LOW) {
      analogWrite(LEFT_MOTOR_PIN, 0);
      analogWrite(RIGHT_MOTOR_PIN, 0);
      buttonPressed = 0;
    } else if (buttonPressed == 1) {
        float distanceLeft = analogRead(SharpSensorLeft);
        float distanceRight = analogRead(SharpSensorRight);
        float distanceForward = analogRead(ThresholdDistance);
    
        convertToCentimetersLeft(distanceLeft);
        convertToCentimetersRight(distanceRight);
        convertToCentimetersForward(distanceForward);

        Serial.print("Distance Left:\t");
        Serial.print(convertedDistanceLeft);
        Serial.print(" cm\t");
        
        Serial.print("Distance Right:\t");
        Serial.print(convertedDistanceRight);
        Serial.println(" cm\t ");
      
        Serial.print("Distance Forward:\t");
        Serial.print(convertedDistanceForward);
        Serial.println(" cm");
        
        if (convertedDistanceForward < 100) {
          if (convertedDistanceRight > convertedDistanceLeft) {
            analogWrite(RIGHT_MOTOR_PIN, 0);
            analogWrite(LEFT_MOTOR_PIN, leftSpeed);
          } else {
            analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
            analogWrite(LEFT_MOTOR_PIN, 0);
          }
        } else {
          Mittenregelung();
        }
    }
    delay(100);
}
