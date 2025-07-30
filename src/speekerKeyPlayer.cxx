#include  <speekerKeyPlayer.h>
#include  <Arduino.h>

SpeekerKeyPlayer::SpeekerKeyPlayer(unsigned int speekerPin, unsigned int shortPin, unsigned int longPin, 
        unsigned int freq, unsigned int shortLength, unsigned int longLength)
{
    _speekerPin = speekerPin;
    _shortPin = shortPin;
    _longPin = longPin;

    _freq = freq;

    _shortLength = shortLength;
    _longLength = longLength;

    pinMode(speekerPin, OUTPUT); // Set buzzer - pin 9 as an output
    pinMode(shortPin, INPUT_PULLUP);
    pinMode(longPin, INPUT_PULLUP);
}

void SpeekerKeyPlayer::sendShort()
{
    tone(_speekerPin, _freq, _shortLength);
    delay(_shortLength);
}

void SpeekerKeyPlayer::sendLong()
{
    tone(_speekerPin, _freq, _longLength);
    delay(_longLength);
}

SpeekerKeyPlayer SpeekerPlayer(buzzer, tip, ring2, freq, shortSignalLengthMS, longSignalLengthMS);