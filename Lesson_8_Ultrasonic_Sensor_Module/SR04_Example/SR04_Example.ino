//Uses a specif libary only made for it 
//It has two input pins not quite sure how they work yet 
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
//Defines the two input pins inside the SRO4 object 
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
//gets a Long that will hold the output of the Ultrasonic Module
long a;

void setup() {
   Serial.begin(9600); //Sent the bit rate to 9600
   pinMode(13, OUTPUT); //Set the board light to be used 
   delay(1000); //Delay after set up
}

void loop() {
   a=sr04.Distance(); //Saves the output of the Ultrasonic into variable a
   Serial.print(a); //Prints the a
   Serial.println("cm"); // prints as string 
   //Checks if the distance is 10cm or less, if object inforn of the ultrasonic is close it will light up the LED
   if(a < 10) 
   {
      digitalWrite(LED_BUILTIN, HIGH);
   }
   else
   {
      digitalWrite(LED_BUILTIN, LOW);
   }
   delay(1000);
   
}
