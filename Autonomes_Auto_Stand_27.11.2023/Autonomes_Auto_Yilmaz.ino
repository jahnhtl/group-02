/*#define Button 2
int ButtonState=0;

                                                                                                                                                                                                                                   
void setup() {

  pinMode(Button, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

  
  
  
  
}
void loop() {
  

  ButtonState=digitalRead(Button);
  
  if(ButtonState == LOW ){
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
  }
  else {
     digitalWrite(6, LOW);
     digitalWrite(5, LOW);
       
  }
}*/
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
 
