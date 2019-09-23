/*
 * This lesson shows us how we can use a 4 Bit Seven Segment display, here all of the bits are connected so they show the same output
 */

 
//Name the pins we are using 
int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS

//Information we want to display 
unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

//Set up the pins as something to use 
void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
}

//Save info to the chip
void Display(unsigned char num)
{

  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);  
}

//Display all the info
void loop() {
  for(int i = 0; i <16; i++)
  {
    Display(i);
    delay(500);
  }
}
