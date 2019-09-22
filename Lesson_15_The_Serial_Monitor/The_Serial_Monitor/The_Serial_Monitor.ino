//In this lesson we integrate the serial port to send information to the board on what lights we want to turn on or off 
//and it what pattern 

int latchPin = 11;
int clockPin = 9;
int dataPin = 12;
int tDelay = 200;

byte leds = 0;
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  updateShiftRegister();
  Serial.begin(9600);
  while (! Serial); // Wait untilSerial is ready - Leonardo
  Serial.println("Enter action, a for front, b for back, c for even, d for odd, e for Blue Yellow,");
  Serial.println("f for Green Red, g for Green Yellow, h for Blue Red and i for Typing");
}

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

//A menu where you maunally can choose which lights to turn on
int typing()
{
    if (Serial.available())
  {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '7')
    {
      int led = ch - '0';
      bitSet(leds, led);
      updateShiftRegister();
      Serial.print("Turned on LED ");
      Serial.println(led);
    }
    if (ch == 'x')
    {
      leds = 0;
      updateShiftRegister();
      Serial.println("Cleared");
    }
    if (ch == 'b')
    {
      Serial.println("Exiting");
      return 1;
    }
    return 0;
  }
}

//Main loop that lets you choose between all of your options 
void loop() 
{
   int whileBreak = 0;
   if (Serial.available())
   {
    char choice = Serial.read();
    if (choice == 'a')
    {
      front();
      Serial.println("Choice = Front");
    }
    else if (choice == 'b')
    {
      back();
      Serial.println("Choice = Back");
    }
    else if (choice == 'c')
    {
      even();
      Serial.println("Choice =  Even");
    }
    else if (choice == 'd')
    {
      odd();
      Serial.println("Choice =  Odd");
    }
    else if (choice == 'e')
    {
      blueYellow();
      Serial.println("Choice =  Blue Yellow");
    }
    else if (choice == 'f')
    {
      greenRed();
      Serial.println("Choice =  Green Red");
    }
    else if (choice == 'g')
    {
      greenYellow();
      Serial.println("Choice =  Green Yellow");
    }
    else if (choice == 'h')
    {
      blueRed();
      Serial.println("Choice =  Blue Red");
    }
    else if (choice == 'i')
    {
      Serial.println("Entering Typing Menu");
      Serial.println("Enter LED Number 0 to 7, or 'x' to clear or 'b' to go back to previous menu");
      while(whileBreak == 0)
      {
        whileBreak = typing();
      }
    }
   }
}
