/*This program is a litte game using the LED from lesson 14
 * It plays out kind of like pong with a ball bouncing between two walls reprensted by LEDs
 * The Outer LEDs are the wall and the moving LED is the ball
 * The user has the abilty to move the walls to whatever postion between 0 and 7 giving the ball more or less room to move in
 * If the user choses the point at which the ball is at the game will make a scoring light show 
 */

//Set up the delay and the pins used from the board
int latchPin = 11;
int clockPin = 9;
int dataPin = 12;
int tDelay = 1000;

//Set up the postions that will be updated 
int upperBound = 7;
int lowerBound = 0;
int current = 0;

//Set up the 8 bit output we send to the IC
byte leds = 0;

//Saves data from board to the IC 
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}


//Sets up the pins to be outputs and lets us use the Serial for input 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  updateShiftRegister();
  Serial.begin(9600);
  while (! Serial); // Wait untilSerial is ready - Leonardo
  Serial.println("Enter a number between 0 to 7, that will determin the walls between which the ball bounces");
  Serial.println("If you choose the spot at which the ball is you get a point");
}

//Wipes the board to be all 0s
void Wipe()
{
  leds = 0;
  updateShiftRegister();
}

//Clears all the LEDS to 0s with excpetion for the upper and lower bounds 
void Clear()
{
  leds = 0;
  bitSet(leds, lowerBound);
  bitSet(leds, upperBound);
  updateShiftRegister();
}

//Moves the ball forward from the lowerbound to the upper bound and waits for user input 
void frontBounce()
{
  for (int i = lowerBound+1; i < upperBound; i++)
  {
    Clear();
    current = i;
    bitSet(leds, i);
    updateShiftRegister();
    if (Serial.available()){typing();}
    delay(tDelay);
  }
}

//Moves the ball bacjward from the lowerbound to the upper bound and waits for user input 
void backBounce()
{
  int counter = 1;
  for (int i = lowerBound+1; i < upperBound; i++)
  {
    Clear();
    current = i;
    bitSet(leds, upperBound-counter);
    counter++;
    updateShiftRegister();
    if (Serial.available()){typing();}
    delay(tDelay);
    
  }
}

void front()
{
  Wipe();
  for (int i = current; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(100);
  }
  current = 0;
}

//Turns on all the lights one by 1 from 7 to 0
void back()
{
  Wipe();
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, 7-i);
    updateShiftRegister();
    delay(100);
  }
}

//Does a little flicker action for scoring 
void hitIt()
{
  front();
  back();
  front();
  back();
}

//Checks for User Input
//If the user clicks anything between 0 or 7 the board will update by moving the wall
//Depending on where the ball is either the easter or wester wall will move to selected postion
//If the wall is placed on the ball a little SCORE visual will play
void typing()
{
 char ch = Serial.read();
 if (ch >= '0' && ch <= '7')
 {
   int led = ch - '0';
   bitSet(leds, led);
   updateShiftRegister();
   if(current > led)
   {
    lowerBound = led;
    Serial.print("Western Wall Shifts to ");
    Serial.println(led);
   }
   else if(current < led)
   {
    upperBound = led;
    Serial.print("Easter Wall Shifts to ");
    Serial.println(led);
   }
   else if(current == led)
   {
     hitIt();
     Serial.println("SCORE");
   }
 }
}


void loop() 
{
  frontBounce();
  backBounce();
}
