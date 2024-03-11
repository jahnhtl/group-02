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


float convertedDistance;
float convertedDistance2;

const float Mittelposition = 50; // Annahme einer mittigen Position (kann je nach Fahrzeug variieren)
const float Toleranz = 5;

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(EmergencyButton, INPUT_PULLUP);
  pinMode(SharpSensorLeft, INPUT);
  pinMode(SharpSensorRight, INPUT);
  pinMode(ThresholdDistance, INPUT);
  
  // Motor Pins als Ausgang setzen
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  
  // Beginnen Sie die serielle Kommunikation mit einer Baudrate von 9600 bps
  Serial.begin(9600);
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

void convertToCentimeters2(int rawValue) {
  // Hier verwenden Sie die spezifische Umrechnungsformel für Ihren Sensor
   convertedDistance2 = 4800 / (rawValue - 20.0);  // Anpassung hier
   if(convertedDistance2 > 120){
    convertedDistance2 = 120;
   }else if(convertedDistance2 < 20){
    convertedDistance2=0;
   }
}

void Mittenregelung(){
  int convertedDistanceLeft=0, convertedDistanceRight=0;
  if (convertedDistanceLeft > convertedDistanceRight + Toleranz) {
          // Das Auto befindet sich zu weit links, daher nach rechts lenken
          analogWrite(LEFT_MOTOR_PIN, leftSpeed);
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed / 5);
        } else if (convertedDistanceRight > convertedDistanceLeft + Toleranz) {
          // Das Auto befindet sich zu weit rechts, daher nach links lenken
          analogWrite(LEFT_MOTOR_PIN, leftSpeed / 5);
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
        } else {
          // Das Auto befindet sich in der Mitte, geradeaus fahren
          analogWrite(LEFT_MOTOR_PIN, leftSpeed);
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
        }
}

void loop() {
    ButtonState = digitalRead(Button);
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
    } else {
        float distanceLeft = analogRead(SharpSensorLeft);
        float distanceRight = analogRead(SharpSensorRight);
        float distanceForward = analogRead(ThresholdDistance);
    
        convertToCentimeters(distanceLeft);
        float convertedDistanceLeft = convertedDistance;
      
        convertToCentimeters(distanceRight);
        float convertedDistanceRight = convertedDistance;
      
        convertToCentimeters2(distanceForward);
        float convertedDistanceForward = convertedDistance;
        
       
        // Ausgabe der Sensorwerte auf dem seriellen Monitor
        Serial.print("Distance Left:\t");
        Serial.print(convertedDistanceLeft);
        Serial.print(" cm\t");
        
        Serial.print("Distance Right:\t");
        Serial.print(convertedDistanceRight);
        Serial.println(" cm\t ");
      
         Serial.print("Distance Forward:\t");
         Serial.print(convertedDistanceForward);
         Serial.print(" cm\t");
        
        Mittenregelung();

        if(convertedDistanceForward < 50 && convertedDistanceForward >= 30 && convertedDistanceRight < 35){
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
          analogWrite(LEFT_MOTOR_PIN, leftSpeed-leftSpeed);
        } else if (convertedDistanceForward < 50 && convertedDistanceForward >= 30 && convertedDistanceLeft < 35){
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed-rightSpeed);
          analogWrite(LEFT_MOTOR_PIN, leftSpeed);
        }
        else{
          analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
          analogWrite(LEFT_MOTOR_PIN, leftSpeed);
        }

    // Eine kurze Verzögerung für die Stabilität der seriellen Kommunikation
    }
  } 