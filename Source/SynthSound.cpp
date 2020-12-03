/*
  ==============================================================================

    SynthSound.cpp
    Created: 29 Nov 2020 5:14:58pm
    Author:  josh

  ==============================================================================
*/

#include "SynthSound.h"

KarplusSound::KarplusSound()
{

}

bool KarplusSound::appliesToNote(int midiNoteNumber)
{
    return true;
}

bool KarplusSound::appliesToChannel(int midiChanel)
{
    return true;
}

