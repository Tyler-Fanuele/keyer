#include <Arduino.h>
#include <keyerSettings.h>
#include <pinsLocations.h>

#include <speekerKeyPlayer.h>
#include <morseTranslater.h>

int tipState = 0;
int ring2State = 0;

int state = 0;

int lastTime = 0;
int currentTime = 0;

int whiteSpaceState = 2;

void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop()
{
  // Poll for pins so we wont just continue to delay dit length
  // Makes more responsive after time without user input
  do {
    currentTime = millis();
    if (whiteSpaceState == 0 && currentTime - lastTime >= longSignalLengthMS)
    {
      const char currentChar = Translator.translate();
      Serial.print(currentChar);
      whiteSpaceState = 1;
    }
    if ( whiteSpaceState == 1 && currentTime - lastTime >= (longSignalLengthMS + longSignalLengthMS + shortSignalLengthMS))
    {
      Serial.print(" ");
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
    
    SpeekerPlayer.sendShort();
    Translator.addDot();
  }
  else if (ring2State == LOW && state != 2)
  {
    state = 2;
    
    SpeekerPlayer.sendLong();
    Translator.addDash();
  }

  lastTime = millis();
  delay(shortSignalLengthMS);
  
}

