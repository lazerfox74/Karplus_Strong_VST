/*
  ==============================================================================

    settings.h
    Created: 30 Nov 2020 6:29:27am
    Author:  josh

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct Settings
{
    AudioSampleBuffer pickBuffer,fingerBuffer,stickBuffer;
    Settings();
    ~Settings();

    enum enumImpulse{pick,finger,stick};
    enumImpulse impulses;

    char impulse{0};

    float dampning{0.4};
    double stereo{1};
    float impulseFilt{50};

};
