/*In this lesson we expand on the lights using a new component that's the photocell, a resitor that can detect light 
 * It's set up as a voltage divider with another resistor and sent to a analog port 
 */

//Set up which pins names go to
int lightPin = 0;
int latchPin = 11;
int clockPin = 9;
int dataPin = 12;

int leds = 0;

//Set up how the pins behave 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}
//Saves the current bits 
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void loop() 
{
  //Reads photo cell
  int reading  = analogRead(lightPin);
  //transforms the data to scale we can use smaller the dividie the less senastive so if we divide by 2 we need small amount of light
  //If we divide by 53 we need a good amount of light 
  int numLEDSLit = reading / 53;  //1023 / 9 / 2
  //Based on the brightness we turn on or off the LEDs
  if (numLEDSLit > 8) numLEDSLit = 8;
  leds = 0;   // no LEDs lit to start
  for (int i = 0; i < numLEDSLit; i++)
  {
    leds = leds + (1 << i);  // sets the i'th bit
  }
  updateShiftRegister();
}
