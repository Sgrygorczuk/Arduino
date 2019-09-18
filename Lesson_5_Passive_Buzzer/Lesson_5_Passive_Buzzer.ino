/*
 * A passive buzzer has a plus inside a circle on it
 * You don't directly create pitches for it like you did with the active buzzer but just give it a frequnecy or a note from  
 * the pitches libary
 */
 
#include "pitches.h"
 
//You can choose notes from the pitches libary, each NOTE_XX is connected to a frequency 
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;  // 500 miliseconds

int melodyTwo[] = {NOTE_GS6, NOTE_CS1, NOTE_CS6, NOTE_GS5, NOTE_E4, NOTE_DS8, NOTE_AS5, NOTE_FS4};
 
void setup() {
 
}
 
void loop() {  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    //The tone function takes in an outputing pin, the note or array of notes and a duration for which it will hold each note for
    tone(8, melodyTwo[thisNote], duration);
     
    // Output the voice after several minutes
    delay(1000);
  }
   
  // restart after two seconds 
  delay(2000);
}
