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
    for (int i = 0; i < 44100; i++)
    {
        delayArray[i] = 0.0;
    }
}

void myDelay::setDelay(int M)
{
    rptr = 0;
    wptr = 0;
    rptr = wptr - M;
    while (rptr < 0) { rptr += 44100; }
    delaySize = M;
}

//https://ccrma.stanford.edu/realsimple/faust_strings/One_Zero_String_Damping_Filter.html
float myDelay::process(float in,float damp,float freqDamp)
{

    float rho = pow(0.001, 1 / (freq * damp));
    a = 1 - freqDamp;
    b = freqDamp;
    z = (in * a) + (z * b);

    return z * rho;
}


float myDelay::delayLine(float sig,float damp,float freqDamp)
{
    float oldSig;


    //delayArray[wptr++] = sig + process(delayArray[wptr],damp);

    delayArray[wptr++] = sig + process(delayArray[wptr],damp,freqDamp);


    //oldSig = (killDelay) ? 0 : delayArray[rptr++];
    oldSig = delayArray[rptr++];


    if (wptr >= delaySize) { wptr = 0; }
    if (rptr >= delaySize) { rptr = 0; }


    return oldSig;

}
