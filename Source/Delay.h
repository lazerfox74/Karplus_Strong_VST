/*
  ==============================================================================

    Delay.h
    Created: 30 Nov 2020 2:11:25pm
    Author:  josh

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//https://ccrma.stanford.edu/~jos/pasp/Variable_Delay_Lines.html

class myDelay
{
public:

    float delayArray[44100];

    int rptr{ 0 };
    int wptr{ 0 };
    int delaySize;

    myDelay();

    void setDelay(int M);

    float b{0.3}, a{ 1 - b }, z{ 0 }, f{ 1 };

    float process(float in,float damp,float freqDamp);

    float delayLine(float sig,float damp,float freqDamp);

    bool killDelay{ false };

    float freq;

};
