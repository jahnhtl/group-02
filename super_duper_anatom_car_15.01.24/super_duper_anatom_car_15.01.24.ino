#define Button 2
#define EmergencyButton 1
#define SharpSensorLeft A0
#define SharpSensorRight A1
#define ThresholdDistance A2

// Motor Pins
#define LEFT_MOTOR_PIN 3
#define RIGHT_MOTOR_PIN 4

int ButtonState = 0;
int EmergencyButtonState = 0;
int buttonPressed = 0;

<<<<<<< HEAD
int leftSpeed = 200;  // Geschwindigkeit für linken Motor (0-255)
int rightSpeed = 200; // Geschwindigkeit für rechten Motor (0-255)

float convertedDistance;
float convertedDistance2;
=======
int leftSpeed = 255;  // Geschwindigkeit für linken Motor (0-255)
int rightSpeed = 255; // Geschwindigkeit für rechten Motor (0-255)
>>>>>>> 90bf1e686dd20c2e3773a6dcc0cee0784d51c582

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(EmergencyButton, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(SharpSensorLeft, INPUT);
  pinMode(SharpSensorRight, INPUT);
  
  // Motor Pins als Ausgang setzen
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  
  // Beginnen Sie die serielle Kommunikation mit einer Baudrate von 9600 bps
  Serial.begin(9600);
}

void moveForward() {
  analogWrite(LEFT_MOTOR_PIN, leftSpeed);
  analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
}

void moveLeft() {
  analogWrite(LEFT_MOTOR_PIN, leftSpeed / 2);  // Reduziere die Geschwindigkeit des linken Motors für eine Linksbewegung
  analogWrite(RIGHT_MOTOR_PIN, rightSpeed);
}

void moveRight() {
  analogWrite(LEFT_MOTOR_PIN, leftSpeed);
  analogWrite(RIGHT_MOTOR_PIN, rightSpeed / 2); // Reduziere die Geschwindigkeit des rechten Motors für eine Rechtsbewegung
}

void moveBackwards() {
  analogWrite(LEFT_MOTOR_PIN, -leftSpeed);  // Ändere die Drehrichtung des linken Motors für eine Rückwärtsbewegung
  analogWrite(RIGHT_MOTOR_PIN, -rightSpeed); // Ändere die Drehrichtung des rechten Motors für eine Rückwärtsbewegung
}

void stopCar() {
  analogWrite(LEFT_MOTOR_PIN, 0);  // Setze die Geschwindigkeit des linken Motors auf 0
  analogWrite(RIGHT_MOTOR_PIN, 0); // Setze die Geschwindigkeit des rechten Motors auf 0
}

void convertToCentimeters(int rawValue) {
  // Hier verwenden Sie die spezifische Umrechnungsformel für Ihren Sensor
<<<<<<< HEAD
   convertedDistance = 4800 / (rawValue - 20.0);  // Anpassung hier
   if(convertedDistance > 80){
    convertedDistance = 80;
   }else if(convertedDistance < 10){
    convertedDistance=0;
   }
}

void convertToCentimeters2(int rawValue) {
  // Hier verwenden Sie die spezifische Umrechnungsformel für Ihren Sensor
   convertedDistance2 = 10650.08 * pow(rawValue,-0.935)-10;  // Anpassung hier
   if(convertedDistance2 > 120){
    convertedDistance2 = 120;
   }else if(convertedDistance2 < 20){
    convertedDistance2=0;
   }
}


=======
  convertedDistance = 4800 / (rawValue - 20.0);  // Anpassung hier
}

>>>>>>> 90bf1e686dd20c2e3773a6dcc0cee0784d51c582
void loop() {
  ButtonState = digitalRead(Button);
  EmergencyButtonState = digitalRead(EmergencyButton);

  if (ButtonState == LOW && buttonPressed == 0) {
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    buttonPressed = 1;
  }

  if (EmergencyButtonState == LOW) {
    stopCar();
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    buttonPressed = 0;
  } else {
<<<<<<< HEAD
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
        Serial.print(" cm \t");
        
        Serial.print("Distance Forward:\t");
        Serial.print(convertedDistanceForward);
        Serial.println(" cm");
        
    
        // Überprüfen Sie, ob auf der linken Seite ein Hindernis ist
        if (convertedDistanceForward < 20 || convertedDistanceRight > 40) {
          moveRight();
        } else{
          moveLeft();
        }
    
        // Überprüfen Sie, ob auf der rechten Seite ein Hindernis ist
        if (convertedDistanceLeft < 20) {
          moveRight();
        }
        if (convertedDistanceRight < 20) {
          moveLeft();
        }
=======
    float distanceLeft = analogRead(SharpSensorLeft);
    float distanceRight = analogRead(SharpSensorRight);
    float distanceForward = analogRead(ThresholdDistance);

    convertToCentimeters(distanceLeft);
    float convertedDistanceLeft = convertedDistance;
  
    convertToCentimeters(distanceRight);
    float convertedDistanceRight = convertedDistance;
  
    convertToCentimeters(distanceForward);
    float convertedDistanceForward = convertedDistance;

    // Ausgabe der Sensorwerte auf dem seriellen Monitor
    Serial.print("Distance Left: ");
    Serial.print(convertedDistanceLeft);
    Serial.print(" cm\t");

    Serial.print("Distance Right: ");
    Serial.print(convertedDistanceRight);
    Serial.println(" cm");

    Serial.print("Distance Forward: ");
    Serial.print(convertedDistanceForward);
    Serial.println(" cm");

    // Überprüfen Sie, ob auf der linken Seite ein Hindernis ist
    if (convertedDistanceRight < 15) {
      moveRight();
    }

    // Überprüfen Sie, ob auf der rechten Seite ein Hindernis ist
    if (convertedDistanceLeft < 15) {
      moveLeft();
    }

    // Wenn Hindernis erkannt, fahre rückwärts und dann, falls links oder rechts frei, fahre zur freien Stelle
    if (cnvertedDistanceLeft < 15 || convertedDistanceRight < 15) {
      moveBackwards();
    
      // Hier könntest du weitere Logik hinzufügen, um zur freien Stelle zu fahren, wenn möglich
    } else {
      // Kein Hindernis erkannt, vorwärts bewegen
      moveForward();
    }
>>>>>>> 90bf1e686dd20c2e3773a6dcc0cee0784d51c582
      }

  // Eine kurze Verzögerung für die Stabilität der seriellen Kommunikation
  delay(100);
}
