//In this lesson we see the print out reads from a Analogue stick, it has three outputs X and Y which are analgoue 
//And there is a click in button which is digital. It also requies to be connected to power and ground. 
//We also incorpmate the RBG LED to physically see the reading of the analgoue stick 
/*
 * The stick has 5 outputs depedning on the postion of the stick and if the button is clicked 
 * First if the button is clicked we will disaply a purple, the base on where the X and Y are we have either 
 * (x,y)
 *  1000,0           1000,500    1000,1000
 *             Blue     |   White
 * 500,0   ------------------------- 500,100
 *             Red      |   Green
 * 0,0               0,500          0,1000     
 */

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

#define BLUE 3 //Connect the 
#define GREEN 4
#define RED 5 

void setup() {
  pinMode(SW_pin, INPUT); //Mark 
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  //Mark the Red, Green and Blue connections as output pins and set the intial power to LOW
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// define variables so that we can modify them before updating the physical componets 
int redValue;
int greenValue;
int blueValue;

void loop() {
  //Loop that looks what is the current status of the analgoue stick and button then sets the variables 
  //in accordance 
  if(digitalRead(SW_pin) == 0)
    {
      redValue = 255;
      greenValue = 0;
      blueValue = 255;
    }
  else if(analogRead(X_pin) <500 && analogRead(Y_pin) < 500)
    {
      redValue = 255;
      greenValue = 0;
      blueValue = 0;
    }
   else if (analogRead(X_pin) > 500  && analogRead(Y_pin) < 500)
   {
      redValue = 0;
      greenValue = 255;
      blueValue = 0;
   }
   else if (analogRead(X_pin) < 500  && analogRead(Y_pin) > 500)
   {
      redValue = 0;
      greenValue = 0;
      blueValue = 255;
   }
   else if (analogRead(X_pin) > 500  && analogRead(Y_pin) > 500)
   {
      redValue = 255;
      greenValue = 255;
      blueValue = 255;
   }

    //Prints out all of the info to the Serial to be double checked 
    Serial.print("Switch:  ");
    Serial.print(digitalRead(SW_pin));
    Serial.print("\n");
    Serial.print("X-axis: ");
    Serial.print(analogRead(X_pin));
    Serial.print("\n");
    Serial.print("Y-axis: ");
    Serial.println(analogRead(Y_pin));
    Serial.print("\n");
    Serial.print("Red: ");
    Serial.println(redValue);
    Serial.print("\n");
    Serial.print("Blue: ");
    Serial.println(blueValue);
    Serial.print("\n");
    Serial.print("Green: ");
    Serial.println(greenValue);
    Serial.print("\n\n");

   //Updates the outputs with the new value of colors
   analogWrite(RED, redValue);
   analogWrite(GREEN, greenValue);
   analogWrite(BLUE, blueValue);
   delay(1000);

}
