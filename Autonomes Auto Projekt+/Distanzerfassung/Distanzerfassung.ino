#define SharpSensorLeft A0 // Pin für den linken Sharp-Sensor
#define SharpSensorRight A1 // Pin für den rechten Sharp-Sensor
#define SharpSensorMiddle A2 // Pin für den mittleren Sharp-Sensor

void setup() {
  Serial.begin(9600); // Start der seriellen Kommunikation
}

void loop() {
  // Rohwerte der Sensoren auslesen
  int sensorLeftValue = analogRead(SharpSensorLeft);
  int sensorRightValue = analogRead(SharpSensorRight);
  int sensorMiddleValue = analogRead(SharpSensorMiddle);

  // Werte auf der seriellen Konsole ausgeben
  Serial.print("Left Sensor Value: ");
  Serial.println(sensorLeftValue);
  Serial.print("Right Sensor Value: ");
  Serial.println(sensorRightValue);
  Serial.print("Middle Sensor Value: ");
  Serial.println(sensorMiddleValue);

  delay(1000); // Eine Sekunde warten, bevor die Werte erneut ausgelesen werden
}
