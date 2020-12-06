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

    myDelay();
    //function for setting up the delay
    void setDelay(int M);

    //function for feeding signals into my delay line
    float delayLine(float sig,float damp,float freqDamp);

    //frequency of my delay
    float freq;

private:
    //my delay array 
    float delayArray[44100];
    //read and write pointer for reading and writing from the circular array buffer.
    //delay size for determing size (frequency) of delay
    int rptr{ 0 }, wptr{ 0 }, delaySize;
    //all variables for use within my onePole Filter
    float b{ 0.3 }, a{ 1 - b }, z{ 0 };
    //function for adding one pole filtering to the signal
    float process(float in, float damp, float freqDamp);



};
