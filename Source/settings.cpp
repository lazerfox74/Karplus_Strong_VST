/*
  ==============================================================================

    settings.cpp
    Created: 30 Nov 2020 6:29:28am
    Author:  josh

  ==============================================================================
*/

#include "settings.h"

Settings::Settings()
{   
    //reading wav impulse files into my audiosamplebuffers
    //MemoryInputStream inputStream(BinaryData::finger_wav, BinaryData::finger_wavSize, false);
    //WavAudioFormat wavFormat;
    //std::unique_ptr<AudioFormatReader> reader(wavFormat.createReaderFor(new MemoryInputStream(BinaryData::finger_wav,BinaryData::finger_wavSize, false), true));
    //pickBuffer.setSize(reader->numChannels, reader->lengthInSamples);
    //reader->read(&pickBuffer, 0, reader->lengthInSamples, 0, true, true);


    //MemoryInputStream inputStream(BinaryData::finger_wav, BinaryData::finger_wavSize, false);
    WavAudioFormat wavFormat;
    std::unique_ptr<AudioFormatReader> reader(wavFormat.createReaderFor(new MemoryInputStream(BinaryData::pick_wav,BinaryData::pick_wavSize, false), true));
    pickBuffer.setSize(reader->numChannels, reader->lengthInSamples);
    reader->read(&pickBuffer, 0, reader->lengthInSamples, 0, true, true);

    WavAudioFormat wavFormat1;
    std::unique_ptr<AudioFormatReader> reader1(wavFormat1.createReaderFor(new MemoryInputStream(BinaryData::stick_wav, BinaryData::stick_wavSize, false), true));
    stickBuffer.setSize(reader1->numChannels, reader1->lengthInSamples);
    reader1->read(&stickBuffer, 0, reader1->lengthInSamples, 0, true, true);

    WavAudioFormat wavFormat2;
    std::unique_ptr<AudioFormatReader> reader2(wavFormat2.createReaderFor(new MemoryInputStream(BinaryData::finger_wav, BinaryData::finger_wavSize, false), true));
    fingerBuffer.setSize(reader2->numChannels, reader2->lengthInSamples);
    reader2->read(&fingerBuffer, 0, reader2->lengthInSamples, 0, true, true);


}
Settings::~Settings()
{

}
