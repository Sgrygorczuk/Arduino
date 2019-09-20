/*This lesson shows off the Thermistor while contiuing with LCD, the thermisor is very good at dectcting temparture 
 * 
 */
#include <LiquidCrystal.h>
//Sets up the analogue pin we are using for the output of the Thermistor 
int tempPin = 0;
//Sets up the pins for LCD 
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup()
{
  lcd.begin(16, 2);
}
void loop()
{
  //Reads the voltage going through the resisotr, basically we created a voltage divider and using that info we are
  //calcuating the temperature 
  int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */

  //Prints out the temperature on the LCD 
  // Display Temperature in C
  lcd.setCursor(0, 0);
  lcd.print("Temp         C  ");
  // Display Temperature in F
  lcd.setCursor(0, 1);
  lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
  lcd.print(tempC);
  // Display Temperature in F
  lcd.setCursor(6, 1);
  lcd.print(tempF);
  delay(500);
}
