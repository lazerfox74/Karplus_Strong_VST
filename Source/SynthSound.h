/*
  ==============================================================================

    SynthSound.h
    Created: 29 Nov 2020 5:14:58pm
    Author:  josh

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class KarplusSound : public SynthesiserSound
{
public:
    KarplusSound();
    bool appliesToNote(int midiNoteNumber) override;
    bool appliesToChannel(int midiChannel) override;

};
