/*This is a lesson on how to use the LCD screen, it has two rows and 17 columns, I used a Potentiometer to contorl the brightness 
 * of the pixels. It simualtes a train going between stations, coutning down for how long till next station, what next station is
 * and showing arriving and departing signs 
 * 
 * 
 * Introduction to the pins of LCD1602:
 * VSS: A pin that connects to ground
 * VDD: A pin that connects to a +5V power supply
 * VO: A pin that adjust the contrast of LCD1602
 * RS: A register select pin that controls where in the LCD’s memory you are writing data to. 
 *      You can select either the data register, which holds what goes on the screen, or an instruction register, 
 *      which is where the LCD’s controller looks for instructions on what to do next.
 * R/W: A Read/Write pin that selects reading mode or writing mode
 * E:An enabling pin that, when supplied with low-level energy, causes the LDC module to execute relevant instructions.
 * D0-D7：Pins that read and write data
 * A and K: Pins that control the LED backlight
 */

//Holds the names of the stops
String Stops[4] = {"A", "B", "C", "D"};
//Amount of time between stops, initally 10 Min but random after
int Time = 10; 
//Acounts for 1 or 2 Columns that the time takes up to dispaly 
int TimeSpace = 1; 
//Keeps track of what stop we're on
int Stop = 0;
//Keeps track of if we're going forwards or backwards 
int FrontBack = 0;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Inites and tells us the dimentions of the LCD 
void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

//If Time = 0 we are then arriving and departing, corresponding disaplys are shown
//The Time gets randomized to a diffrent lenght and the current stop and direction are updated
void arriveDepart()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Arriving at ");
    lcd.setCursor(12, 0);
    lcd.print(Stops[Stop]);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Deprating from ");
    lcd.setCursor(15, 0);
    lcd.print(Stops[Stop]);
    delay(1000);
    lcd.clear();
    Time = random(15);
    if(FrontBack == 0)
    {
      Stop++;
      if(Stop == 3){FrontBack = 1;}
    }
    else
    {
      Stop--;
      if(Stop == 0){FrontBack = 0;}
     }
}

//Shows the count down till the next stop
void currentStop()
{
  lcd.setCursor(0, 0);
  lcd.print("Train in "); 
  lcd.setCursor(9, 0);
  lcd.print(Time); 
  if(Time < 10){TimeSpace = 1;}
  else{TimeSpace = 2;}
  lcd.setCursor(10 + TimeSpace, 0);
  lcd.print("Min"); 
  lcd.setCursor(0, 1);
  lcd.print("Next stop is ");
  lcd.setCursor(14,1); 
  lcd.print(Stops[Stop]);
}

//1 in 12 chance a Sponsored MTA message appears between stops 
void MTALoveMessage()
{
  String messages[4] = {"MTA is watching", "Eat Food, Be Good", "Fare is $15", "Have a good day!"};
  int message = random(12);
  if(message == 3)
  {
    message = random(3);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(messages[message]);
    Time--;
    delay(1000);
  }
}

//Main loops 
void loop() {
  lcd.clear();
  if(Time < 0)
  {
    arriveDepart();
  }
  currentStop();
  MTALoveMessage();
  Time--;
  delay(1000);
}
