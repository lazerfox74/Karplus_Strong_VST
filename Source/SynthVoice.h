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
    //creating a Settings pointer so it can be used to point to my global settings object
    Settings* voiceSettings;

    
private:
    //level for scaling the volume of my output, liveSample for playback of my Impulse sample and Output for being the output of combined impulse and delay
    float level{ 0.5 }, liveSample{ 0.0 }, output{1};
    //postion used as incrementer for impulse sample
    int position{0};
    //play used for logic for playing impulse
    bool play{ false };
    //arry of delay objects for left and right channel
    myDelay voiceDelay[2];
    //filter for filtering my impulse sample
    IIRFilter filter;
    //variable for setting filter frequency
    float filterFreq{400};

    //int StartSampleRate{0};


};