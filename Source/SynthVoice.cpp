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
    
    position = 0;
    liveSample = 0;
    play = true;

    //set delay time according to midinote
    double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    //setting my impulse filter
    filter.setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), *voiceSettings->impulseFiltPointer, 1.0));
    
    //setting the frequency for my delays
    voiceDelay[0].freq = cyclesPerSecond;
    voiceDelay[1].freq = cyclesPerSecond;
    //offsetting my delay length based on stereo value
    int delayFrequencyL = (getSampleRate() / (cyclesPerSecond * *voiceSettings->stereoPointer ));
    int delayFrequencyR = (getSampleRate() / (cyclesPerSecond * (1/ *voiceSettings->stereoPointer)));

    //setting the delay of my voices
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
    //logic for deciging which impulse to set my current impulse variable to
    if (*voiceSettings->pickPointer > 0.5f) {currentImpulse = voiceSettings->pickBuffer;}
    else if(*voiceSettings->fingerPointer > 0.5) { currentImpulse = voiceSettings->fingerBuffer; }
    else { currentImpulse = voiceSettings->stickBuffer;}

    while (--numSamples >= 0)
    {
        //stopping my impulse from playing if it exceeds the number of samples in my current impulse
        if (position > currentImpulse.getNumSamples() - 1)
        {
            position = 0;
            play = false;
        }
        //playing my sample and adding delay
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
            output = liveSample * level + voiceDelay[i].delayLine(liveSample, *voiceSettings->dampPointer,*voiceSettings->freqDampPointer) * level;

            outputBuffer.addSample(i,startSample,(output));

        }
        //incrementing index for writing to output buffer
        ++startSample;
        //increnting position in sample playback
        ++position;


    }


}
