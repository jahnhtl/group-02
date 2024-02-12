#define Button 2
#define EmergencyButton 1
#define SharpSensorLeft A0
#define SharpSensorRight A1
//#define ThresholdDistance A2

// Motor Pins
#define LEFT_MOTOR_PIN 5
#define RIGHT_MOTOR_PIN 6

int ButtonState = 0;
int EmergencyButtonState = 0;
int buttonPressed = 0;

int leftSpeed = 240;  // Geschwindigkeit für linken Motor (0-255)
int rightSpeed = 240; // Geschwindigkeit für rechten Motor (0-255)

float convertedDistance;
float convertedDistance2;


void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(EmergencyButton, INPUT_PULLUP);
  pinMode(SharpSensorLeft, INPUT);
  pinMode(SharpSensorRight, INPUT);
  
  // Motor Pins als Ausgang setzen
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  
  // Beginnen Sie die serielle Kommunikation mit einer Baudrate von 9600 bps
  Serial.begin(115200);
}



void convertToCentimeters(int rawValue) {
  // Hier verwenden Sie die spezifische Umrechnungsformel für Ihren Sensor
   convertedDistance = 4800 / (rawValue - 20.0);  // Anpassung hier
   if(convertedDistance > 80){
    convertedDistance = 80;
   }else if(convertedDistance < 10){
    convertedDistance=0;
   }
}

/*void convertToCentimeters2(int rawValue) {
  // Hier verwenden Sie die spezifische Umrechnungsformel für Ihren Sensor
   convertedDistance2 = 10650.08 * pow(rawValue,-0.935)-10;  // Anpassung hier
   if(convertedDistance2 > 120){
    convertedDistance2 = 120;
   }else if(convertedDistance2 < 20){
    convertedDistance2=0;
   }
}
*/

void loop() {
    /*  ButtonState = digitalRead(Button);
    EmergencyButtonState = digitalRead(EmergencyButton);

    if (ButtonState == LOW && buttonPressed == 0) {
      analogWrite(LEFT_MOTOR_PIN, leftSpeed);
      analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
      buttonPressed = 1;
    }

    if (EmergencyButtonState == LOW) {
      analogWrite(LEFT_MOTOR_PIN, leftSpeed-leftSpeed);
      analogWrite(RIGHT_MOTOR_PIN, rightSpeed-rightSpeed);
      buttonPressed = 0;
    } else {*/
        float distanceLeft = analogRead(SharpSensorLeft);
        float distanceRight = analogRead(SharpSensorRight);
        //float distanceForward = analogRead(ThresholdDistance);
    
        convertToCentimeters(distanceLeft);
        float convertedDistanceLeft = convertedDistance;
      
        convertToCentimeters(distanceRight);
        float convertedDistanceRight = convertedDistance;
      
        /*convertToCentimeters2(distanceForward);
        float convertedDistanceForward = convertedDistance;
        */
        /*
        // Ausgabe der Sensorwerte auf dem seriellen Monitor
        Serial.print("Distance Left:\t");
        Serial.print(convertedDistanceLeft);
        Serial.print(" cm\t");
        
        Serial.print("Distance Right:\t");
        Serial.print(convertedDistanceRight);
        Serial.println(" cm ");
      */
        //   Serial.print("Distance Forward:\t");
        //   Serial.print(convertedDistanceForward);
        //   Serial.println(" cm");
        
        if(convertedDistanceRight > 43 && convertedDistanceLeft < 43){
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
          analogWrite(LEFT_MOTOR_PIN, leftSpeed/5);

        } else if(convertedDistanceRight < 43 && convertedDistanceLeft > 43){
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed/5);
          analogWrite(LEFT_MOTOR_PIN, leftSpeed);

        } else{
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
          analogWrite(LEFT_MOTOR_PIN, leftSpeed);
        }

    // Eine kurze Verzögerung für die Stabilität der seriellen Kommunikation
  
}