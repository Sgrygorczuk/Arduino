/*
 * This lesson shows us how we can use a 4 Bit Seven Segment display dispalying diffrent numbers on each seven segment bit
 * When you send info to it will display it on every display that is LOW, thus you want to do a LOW to HIGH transiton that 
 * updates that bit, however it has no memory so there is no way to just keep that number there, if you turn on all of the 
 * bits to LOW they will all display the same number. So the get the effect of having multiple images on the display 
 * you quickly jumped between them sending diffrent info to each with a refresh rate that make it look like a constant 
 * light but in fact each one is cosntaly updating and resting indivually. 
 * 
 * This project uses the Shift Register to break a hex code into 8 bit info for the abcdefg inputs to read
 * 
 * The idea behind it is a clock which counts minutes and seconds 
 * 
 * This code broke the set up at one point so don't use it.
 */

 
//Name pins that go to the IC and to the lights of the Seven Segment Display 
int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS
int D1 = 2;
int D2 = 3;
int D3 = 4;
int D4 = 5;

//Information we want to display 
unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

//Set counters 
int seconds = 0;
int Digit1 = 0;
int Digit2 = 0;
int Digit3 = 0;
int Digit4 = 0;

//Set up the pins as something to use 
void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
}

//Updates each Seven Segment Dispaly 
void Display()
{
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  
  digitalWrite(latch,LOW);
  digitalWrite(D1,LOW);
  shiftOut(data,clock,MSBFIRST,table[Digit2]);
  delay(2);
  digitalWrite(D1,HIGH);
  digitalWrite(latch,HIGH);
  delay(2);

  digitalWrite(latch,LOW);
  digitalWrite(D2,LOW);
  shiftOut(data,clock,MSBFIRST,table[Digit3]);
  delay(2);
  digitalWrite(D2,HIGH);
  digitalWrite(latch,HIGH);
  delay(2);

  digitalWrite(latch,LOW);
  digitalWrite(D3,LOW);
  shiftOut(data,clock,MSBFIRST,table[Digit4]);
  delay(2);
  digitalWrite(D3,HIGH);
  digitalWrite(latch,HIGH);
  delay(2);

  digitalWrite(latch,LOW);
  digitalWrite(D4,LOW);
  shiftOut(data,clock,MSBFIRST,table[Digit1]);
  delay(2);
  digitalWrite(D4,HIGH);
  digitalWrite(latch,HIGH);
  delay(2);
   
}

//Display all the and updates counter 
void loop() 
{
  if(Digit1 == 5 && Digit2 == 9)
  {
    Digit1 = 0;
  }
  else if(Digit2 > 9)
  {
    Digit1++;
    Digit2 = 0;
  }
  else if(Digit3 == 5 && Digit4 == 9)
  {
    Digit2++;
    Digit3 = 0;
    Digit4 = 0;
  }
  else if(Digit4 > 9)
  {
    Digit3++;
    Digit4 = 0;
  }
  else if(1000 - seconds < 0)
  {
    Digit4++;
    seconds = 0;
  }
  Display();
  seconds += 20;
  
}
