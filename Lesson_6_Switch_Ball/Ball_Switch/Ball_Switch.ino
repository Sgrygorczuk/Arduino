/*****************************************/
const int ledPin = 13;//the led attach to

void setup()
{ 
  pinMode(ledPin,OUTPUT);//initialize the ledPin as an output
  pinMode(2,INPUT);
  digitalWrite(2, HIGH);
} 
/******************************************/
void loop() 
{  
  //Reads the Ball Swtich and checks if it is in an upright postion, if it isn't LED is off
  //if it is LED is on, if Switch ball is upright it's value is LOW else it's HIGH
  int digitalVal = digitalRead(2);
  if(HIGH == digitalVal)
  {
    digitalWrite(ledPin,LOW);//turn the led off
  }
  else
  {
    digitalWrite(ledPin,HIGH);//turn the led on 
  }
}
/**********************************************/
