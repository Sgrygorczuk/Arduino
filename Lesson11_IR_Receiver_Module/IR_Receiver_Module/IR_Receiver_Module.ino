//G = GND R = VCC Y = DATA
//In this lesson we work with a IR reader and controller. The contorller has 21 diffrent buttons which send diifrent intensity of the light which the reciver reads.
//In addtion to see the the physical effects I connceted the project to the to the RBG LED similar to that of previous project 
#include "IRremote.h"

//Connect the pins to numbers 
#define BLUE 3 //Connect the 
#define GREEN 4
#define RED 5 
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

//Set variables that will keep track of the states of the light
int OnOff = 0; 
int redValue = 0;
int blueValue = 0;
int greenValue = 0; 
int pastRedValue = 0;
int pastBlueValue = 0;
int pastGreenValue = 0; 


//Declare the IR objects 
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

//Updates we send to the Serial 
void translateIR() // takes action based on IR code received
// describing Remote IR codes 
{
  Serial.print("\n");
  Serial.print("Red: ");
  Serial.println(redValue);
  Serial.print("Blue: ");
  Serial.println(blueValue);
  Serial.print("Green: ");
  Serial.println(greenValue);
   Serial.print("Old Red: ");
  Serial.println(pastRedValue);
  Serial.print("Old Blue: ");
  Serial.println(pastBlueValue);
  Serial.print("Old Green: ");
  Serial.println(pastGreenValue);
  Serial.print("On/Off: ");
  Serial.println(OnOff);
  Serial.print("\n\n"); 
  switch(results.value)
  {
  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1");    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3");    break;
  case 0xFF10EF: Serial.println("4");    break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button : ");
    Serial.println(results.value);

  }// End Case
} //END translateIR

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

  
  //Mark the Red, Green and Blue connections as output pins and set the intial power to LOW
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

//Saves the colors so we can go back to them
void Save()
{
  pastRedValue = redValue;
  pastBlueValue = blueValue;
  pastGreenValue = greenValue; 
}

//Increases the values of each by 5 unless one of the values is 255 or more 
void incCheck()
{
  greenValue += 5;
  redValue += 5;
  blueValue += 5;
  
  if(redValue > 255)
  {
    redValue = 255;
  }
  if(blueValue > 255)
  {
    blueValue = 255;
  }
  if(greenValue > 255)
  {
    greenValue = 255;
  }
}

//Decreases the values of each by 5 unless one of the values is 0 or less
void decCheck()
{
  greenValue -= 5;
  redValue -= 5;
  blueValue -= 5;
  
  if(redValue < 0)
  {
    redValue = 0;
  }
  if(blueValue < 0)
  {
    blueValue = 0;
  }
  if(greenValue < 0)
  {
    greenValue = 0;
  }
}

//Turns the light on and off, using the power button.
//If the LED is on we can change the lights, increase or decrease the intenisty 
//Can go back to the previous light if clicked fast back 
void ControlLED()
{
  if( results.value == 0xFFA25D)
  {
    if (OnOff == 0)
    {
      redValue = 255;
      greenValue = 255;
      blueValue = 255;
      OnOff = 1;
    }
    else if (OnOff == 1)
    {
      redValue = 0;
      greenValue = 0;
      blueValue = 0;
      OnOff = 0; 
    }
  }
  if(OnOff == 1)
  {
    switch(results.value)
    {
    /*case 0xFFE21D: //FUNC/STOP
      break;
    */
    case 0xFF629D: //VOL+
      {
        incCheck();
        break;
      }
    //For whatever reason this dosen't work need to go back to it, probably just order of operations 
    case 0xFF22DD: //Fast Back go back to previous color F
      {
        redValue = pastRedValue;
        greenValue = pastGreenValue;
        blueValue = pastBlueValue;
        break;
      }
   /* case 0xFF02FD: //PAUSE
      break;
    case 0xFFC23D: //FAST FORWARD
      break;
    case 0xFFE01F: //DOWN
      break;
    */
    case 0xFFA857: //VOL -
      {
        decCheck();
        break;
      }
    /*
    case 0xFF906F: //UP
      break;
    case 0xFF9867: //EQ
      break;
    case 0xFFB04F: // ST/REPT    
      break;
    */
    case 0xFF6897: //0
      {
        redValue = 255;
        greenValue = 0;
        blueValue = 0;
        break;
      }
    case 0xFF30CF: //1
    {
        redValue = 0;
        greenValue = 255;
        blueValue = 0;
        break;
    }
    case 0xFF18E7: //2
    {
        redValue = 0;
        greenValue = 0;
        blueValue = 255;
        break;
    }
    case 0xFF7A85: //3 
    {
        redValue = 255;
        greenValue = 255;
        blueValue = 0;
        break;
    }
    case 0xFF10EF: //4
    {
        redValue = 255;
        greenValue = 0;
        blueValue = 255;
        break;
    }
    case 0xFF38C7:  //5  
    {
        redValue = 0;
        greenValue = 255;
        blueValue = 255;
        break;
    }
    case 0xFF5AA5: //6
    {
        redValue = 255;
        greenValue = 127;
        blueValue = 255;
        break;
    }
    case 0xFF42BD: //7
    {
        redValue = 127;
        greenValue = 255;
        blueValue = 255;
        break; 
    }
    case 0xFF4AB5: //8
    {
        redValue = 127;
        greenValue = 255;
        blueValue = 127;
        break; 
    }
    case 0xFF52AD: //9
    {
      redValue = 127;
      greenValue = 127;
      blueValue = 127;
      break; 
    }
    /*case 0xFFFFFFFF: //REPEAT
      break; 
    */ 
    }
  }
  Save();
}

void loop()
{
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    ControlLED();
    translateIR();
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);
    delay(500); // Do not get immediate repeat

    irrecv.resume(); // receive the next value
  }  
}
