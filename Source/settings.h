/*
  ==============================================================================

    settings.h
    Created: 30 Nov 2020 6:29:27am
    Author:  josh

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//settings struct to be used to store settings so other classes can be sent the settings as a reference
struct Settings
{
    ///audioSampleBuffer objects for storing my impulse samples
    AudioSampleBuffer pickBuffer,fingerBuffer,stickBuffer;
    Settings();
    ~Settings();

    ////enum for the playing the relevant impulse sample 
    enum enumImpulse{pick,finger,stick};
    enumImpulse impulses;

    char impulse{2};

    //pointers to point to the values in my AudioProcessorValueTreeState
    std::atomic<float>* dampPointer = nullptr;
    std::atomic<float>* stereoPointer = nullptr;
    std::atomic<float>* impulseFiltPointer = nullptr;
    std::atomic<float>* freqDampPointer = nullptr;

    std::atomic<float>* pickPointer = nullptr;
    std::atomic<float>* fingerPointer = nullptr;
    std::atomic<float>* stickPointer = nullptr;

};
