/*
  ==============================================================================

    Delay.cpp
    Created: 30 Nov 2020 2:11:25pm
    Author:  josh

  ==============================================================================
*/

#include "Delay.h"

myDelay::myDelay()
{
    //initialising delay with silence
    for (int i = 0; i < 44100; i++)
    {
        delayArray[i] = 0.0;
    }
}

void myDelay::setDelay(int M)
{
    //setting up my read and write pointers
    rptr = wptr - M;
    while (rptr < 0) { rptr += 44100; }
    //setting my delay size to the lenght of my delay
    delaySize = M;
}

float myDelay::process(float in,float damp,float freqDamp)
{
    //finding the nth root of 0.001 to calculate a dampning scaler that will give the same decay length irrelevant of delay frequency 
    float dampScale = pow(0.001, 1 / (freq * damp));
    //setting up one pole filter variables
    a = 1 - freqDamp;
    b = freqDamp;
    //achieveing dampning not letting the input directly effect the output
    z = (in * a) + (z * b);
    return z * dampScale;
}


float myDelay::delayLine(float sig,float damp,float freqDamp)
{
 
    float oldSig;
    //setting the value at the write pointer to current signal
    delayArray[wptr++] = sig + process(delayArray[wptr],damp,freqDamp);

    //setting the oldSignal to the value at the readpointer
    oldSig = delayArray[rptr++];

    //logic for creating circular buffer
    if (wptr >= delaySize) { wptr = 0; }
    if (rptr >= delaySize) { rptr = 0; }

    //returing delayed signal
    return oldSig;

}
