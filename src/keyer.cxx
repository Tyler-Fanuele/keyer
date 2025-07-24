#include <Arduino.h>


const int buzzer = 2; //buzzer to arduino pin 9
const int tip = 8;
const int ring2 = 7;

const int freq = 420;


// Here's a breakdown of the timing elements:

// Dot: The shortest unit of Morse code, lasting for one time unit. 
// Dash: Three times the length of a dot, or three time units. 
// Intra-character space: The space between the dots and dashes within a single character is one time unit, according to RoboBlocky. 
// Inter-character space: The space between letters within a word is three time units. 
// Inter-word space: The space between words is seven time units

const int WPM = 20;
const int ditLength = 60000 / (WPM * 50);
const int dahLength = ditLength * 3;

int tipState = 0;
int ring2State = 0;

int state = 0;

int lastTime = 0;
int currentTime = 0;

int whiteSpaceState = 2;

void sendDah()
{
  tone(buzzer, freq, dahLength); 
  delay(dahLength);
}

void sendDit()
{
  tone(buzzer, freq, ditLength);
  delay(ditLength);
}

void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(tip, INPUT_PULLUP);
  pinMode(ring2, INPUT_PULLUP);
}

void loop()
{

  // Poll for pins so we wont just continue to delay dit length
  // Makes more responsive after time without user input
  do {
    currentTime = millis();
    if (whiteSpaceState == 0 && currentTime - lastTime >= dahLength)
    {
      Serial.print(" ");
      whiteSpaceState = 1;
    }
    if ( whiteSpaceState == 1 && currentTime - lastTime >= (dahLength + dahLength + ditLength))
    {
      Serial.print(" | ");
      whiteSpaceState = 2;
    }
    
    tipState = digitalRead(tip);
    ring2State = digitalRead(ring2);
  } while (tipState != LOW && ring2State != LOW);

  whiteSpaceState = 0;

  // Check to see if we have dah pressed after dit was pressed.
  // Allows for oscillating between dit and dah when dah is first
  if (ring2State == LOW && state == 1)
  {
    state = 1;
  }
  else
  {
    state = 0;
  }
  

  if (tipState == LOW && state != 1)
  {
    state = 1;
    Serial.print(".");
    sendDit();
  }
  else if (ring2State == LOW && state != 2)
  {
    state = 2;
    Serial.print("-");
    sendDah();
  }

  lastTime = millis();
  delay(ditLength);
  
}

