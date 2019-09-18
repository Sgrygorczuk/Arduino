//www.elegoo.com
//2016.12.08


//Sets Button A to be pin 9, sets Button B to be pin 8, and sends LED to be pin 5
int ledPin = 5;
int buttonApin = 9;
int buttonBpin = 8;

byte leds = 0;

//Uses the preset values to be input or output variables 
void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}

//When either of the Buttons is pressed is saves the state of the button to either High or Low based on which button is pressed
//And waits till next time a button is pressed to update it
void loop() 
{
  //If Button A is not pushed then the light is turned On
  if (digitalRead(buttonApin) == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
  //If the Button B is not pushed the LED is off 
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
}
