/*
  ==============================================================================

    SynthVoice.h
    Created: 29 Nov 2020 5:14:50pm
    Author:  josh

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "settings.h"
#include "Delay.h"

class KarplusVoice : public SynthesiserVoice
{
public:

    KarplusVoice(Settings* vSettings);

    bool canPlaySound(SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/) override;

    void stopNote(float /*velocity*/, bool allowTailOff) override;

    void pitchWheelMoved(int /*newValue*/) override;

    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    using SynthesiserVoice::renderNextBlock;

    Settings* voiceSettings;

    
private:

    float level{ 1 }, delaySig{ 0.0 }, liveSample{ 0.0 }, output{1};
    double tailOff{ 0.0 };
    int position{0};
    bool play{ false };

    myDelay voiceDelay[2];

    IIRFilter filter;

    float filterFreq{400};
    bool active;

    int StartSampleRate{0};


};