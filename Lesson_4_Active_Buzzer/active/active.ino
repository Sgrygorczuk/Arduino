//www.elegoo.com
//Active Buzzer has a Square Plus on the surface 
// Active buzzer project has one output of whatever pin you choose in this case pin 12 and connect to the ground 
//You can choose the frequency by having a noise repeate n times for instance 80 and switch between high and low creating 
//Square waves where it is making and not making noise, seting delay to be 1 gives you 1 ms of wating
//You can have multiple freqeuencies appear in between each other which combine into one big frequnecy such as the one below

int buzzer = 12;//the pin of the active buzzer
void setup()
{
 pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
}

/*
Drawing a graph is hard but basically the square wave looks like this 
1111 1111 1100 | 1111 1111 1100 0000 0000 | 1111 1000 1111 1000 1111 1000 1111 1000 |
*/

void loop()
{
 unsigned char i;
 unsigned char j;
 while(1)
 {  
    //This sengement creates the 
    //1111 1111 1100 
    digitalWrite(buzzer,HIGH);
    delay(10);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(2);//wait for 1ms
   //output an frequency
   for(i=0;i<80;i++)
   {
    /*
    This segment creates 
    1111 1111 1100 0000 0000 
    Two iterations of this noise will create a signal as such 
    i = 0                    | j = 0     | j = 1     | j = 2     | j = 3     | i = 1 
    1111 1111 1100 0000 0000 | 1111 1000 | 1111 1000 | 1111 1000 | 1111 1000 | 1111 1111 1100 0000 0000 
    Where next would be j = 0 - 4 creating this unique frequency
    */
    digitalWrite(buzzer,HIGH);
    delay(10);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(10);//wait for 1ms
         for(j=0;i<4;i++)
        {  
              /*
              This segment creates
              1111 1000 which is repated 4 times 
              Giving this
              1111 1000 1111 1000 1111 1000 1111 1000
              After that we return to pervousl loop 
              */
              digitalWrite(buzzer,HIGH);
              delay(5);//wait for 1ms
              digitalWrite(buzzer,LOW);
              delay(3);//wait for 1ms
        }
    }
  }
} 
