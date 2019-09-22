//This lesson shows how to use the 74HC595 Shift IC to extend the output of three digital pins on the arduion to 8 or more outputs
//It uses a dataPin which takes in the information of an byte array 

int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

//Byte is a data types that holds 8 Binary spots 
byte leds = 0;

//Writes to the register 
void updateShiftRegister()
{
   //Allows for input 
   digitalWrite(latchPin, LOW);
   //Inputs the leds array
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   //closes for input and saves 
   digitalWrite(latchPin, HIGH);
}

//Sets up that the pins are all outptus 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

/*bitSet()
 * Sets (writes a 1 to) a bit of a numeric variable.
 * bitSet(x, n)
 * x: the numeric variable whose bit to set.
 * n: which bit to set, starting at 0 for the least-significant (rightmost) bit.
 */

//Clears all the LEDS to 0
void Clear()
{
  leds = 0;
  updateShiftRegister();
  delay(tDelay);
}

//Turns on all the lights one by 1 from 0 to 7
/*i =  0           1           2           3           4           5           6           7        
 * 1000 0000 | 1100 0000 | 1110 0000 | 1111 0000 | 1111 1000 | 1111 1100 | 1111 1110 | 1111 1111 
 */
void front()
{
  Clear();
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}

//Turns on all the lights one by 1 from 7 to 0
/*i =  0           1           2           3           4           5           6           7        
 * 0000 0001 | 0000 0011 | 0000 0111 | 0000 1111 | 0001 1111 | 0011 1111 | 0111 1111 | 1111 1111 
 */
void back()
{
  Clear();
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, 7-i);
    updateShiftRegister();
    delay(tDelay);
  }
}

//Turns on all the even lights
/*i =  0           1           2           3             
 * 1000 0000 | 1010 0000 | 1010 1000 | 1010 1010 
 */
void even()
{
  Clear();
  for (int i = 0; i < 4; i++)
  {
    bitSet(leds, 2*i);
    updateShiftRegister();
    delay(tDelay);
  }
}


//Turns on all the odd lights
/*i =  1           2           3           4             
 * 0100 0000 | 0101 0000 | 0101 0100 | 0101 0101 
 */
void odd()
{
  Clear();
  for (int i = 1; i < 5; i++)
  {
    bitSet(leds, 2*i-1);
    updateShiftRegister();
    delay(tDelay);
  }
}

//Turns on all only the blue and yellow lights (Physical Color order -> BBGGYYRR)
/*i =  0           1           4           5             
 * 1000 0000 | 1100 0000 | 1100 1000 | 1100 1100 
 */
void blueYellow()
{
  Clear();
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    if(i%2 == 1){i = i + 2;}
    delay(tDelay);
  }
}

//Turns on all only the green and red lights (Physical Color order -> BBGGYYRR)
/*i =  2           3           6           7             
 *0010 0000 |  0011 0000 | 0011 0010 | 0011 0011 
 */
void greenRed()
{
  Clear();
  for (int i = 2; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    if(i%2 == 1){i = i + 2;}
    delay(tDelay);
  }
}

//Turns on all only the blue and red lights (Physical Color order -> BBGGYYRR)
/*i =  0           1           6           7             
 *1000 0000 |  1100 0000 | 1100 0010 | 1100 0011 
 */
void blueRed()
{
  Clear();
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    if(i%2 == 1){i = i + 4;}
    delay(tDelay);
  }
}

//Turns on all only the green and yellow lights (Physical Color order -> BBGGYYRR)
/*i =  2           3           4           5             
 *0010 0000 | 0011 0000 | 0011 1000 | 0011 1100
 */
void greenYellow()
{
  Clear();
  for (int i = 2; i < 6; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}

void loop() 
{
  front();
  back();
  blueRed();
  greenYellow();
  greenRed();
  blueYellow();
  even();
  odd();
}
