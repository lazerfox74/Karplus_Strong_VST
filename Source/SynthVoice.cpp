/*
  ==============================================================================

    SynthVoice.cpp
    Created: 29 Nov 2020 5:14:50pm
    Author:  josh

  ==============================================================================
*/

#include "SynthVoice.h"

KarplusVoice::KarplusVoice(Settings* vSettings)
{
    voiceSettings = vSettings;
    
}

bool KarplusVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<KarplusSound*> (sound) != nullptr;
}

void KarplusVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    level = 0.5;
    position = 0;
    liveSample = 0;
    play = true;

    //set delay time according to midinote
    double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

    filter.setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), voiceSettings->impulseFilt, 1.0));

    filterFreq = cyclesPerSecond;

    active = true;

    voiceDelay[0].freq = cyclesPerSecond;
    voiceDelay[1].freq = cyclesPerSecond;

    int delayFrequencyL = (getSampleRate() / (cyclesPerSecond * voiceSettings->stereo ));
    int delayFrequencyR = (getSampleRate() / (cyclesPerSecond * (1/voiceSettings->stereo)));


    voiceDelay[0].setDelay(delayFrequencyL);
    voiceDelay[1].setDelay(delayFrequencyR);

}

void KarplusVoice::stopNote(float /*velocity*/, bool allowTailOff)
{

}


void KarplusVoice::pitchWheelMoved(int /*newValue*/)
{

}

void KarplusVoice::controllerMoved(int /*controllerNumber*/, int /*newValue*/)
{

}


void KarplusVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    AudioSampleBuffer currentImpulse;
    switch (voiceSettings->impulse)
    {
    case 0:
        currentImpulse = voiceSettings->pickBuffer;
        break;
    
    case 1:
        currentImpulse = voiceSettings->fingerBuffer;
        break;
    case 2:
        currentImpulse = voiceSettings->stickBuffer;
        break;
    }
    while (--numSamples >= 0)
    {

        if (position > currentImpulse.getNumSamples() - 1)
        {
            position = 0;
            play = false;
        }

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
        {
            if (play)
            {
                liveSample = filter.processSingleSampleRaw(currentImpulse.getSample(0, position) * 0.5);
            }
            else
            {
                liveSample = 0.0;
            }
            output = liveSample * level + voiceDelay[i].delayLine(liveSample, voiceSettings->dampning) * level;

            outputBuffer.addSample(i,startSample,(output));

        }

        ++startSample;
        ++position;


    }


}
