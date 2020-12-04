/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Karplus_finalAudioProcessor::Karplus_finalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    parameters(*this,nullptr)
#endif
{
    NormalisableRange<float> dampRange(0.01f, 10.0f);
    NormalisableRange<float> steroRange(1.0f, 1.3f);
    NormalisableRange<float> impRange(200.0f, 15000.0f);
    NormalisableRange<float> freqDampRange(0.1f, 0.99f);


    parameters.createAndAddParameter(DAMP_ID, DAMP_NAME, DAMP_NAME, dampRange, 5.0f, nullptr, nullptr);
    parameters.createAndAddParameter(STEREO_ID, STEREO_NAME, STEREO_NAME, steroRange, 1.0f, nullptr, nullptr);
    parameters.createAndAddParameter(IMP_ID, IMP_NAME, IMP_NAME, impRange, 200.0f, nullptr, nullptr);
    parameters.createAndAddParameter(FREQDAMP_ID, FREQDAMP_NAME, FREQDAMP_NAME, freqDampRange, 0.4f, nullptr, nullptr);


    parameters.state = ValueTree("savedParams");

    synth.clearVoices();

    for (int i = 0; i < 8; ++i)
    {
        synth.addVoice(new KarplusVoice(&globalSettings));   // These voices will play our custom sine-wave sounds..
    }

    synth.clearSounds();
    synth.addSound(new KarplusSound());
}

Karplus_finalAudioProcessor::~Karplus_finalAudioProcessor()
{
}

//==============================================================================
const String Karplus_finalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Karplus_finalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Karplus_finalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Karplus_finalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Karplus_finalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Karplus_finalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Karplus_finalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Karplus_finalAudioProcessor::setCurrentProgram (int index)
{
}

const String Karplus_finalAudioProcessor::getProgramName (int index)
{
    return {};
}

void Karplus_finalAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Karplus_finalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);

}

void Karplus_finalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Karplus_finalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Karplus_finalAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples()); // [5]


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Karplus_finalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Karplus_finalAudioProcessor::createEditor()
{
    return new Karplus_finalAudioProcessorEditor (*this);
}

//==============================================================================
void Karplus_finalAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr <juce::XmlElement> xmlState(parameters.state.createXml());
    copyXmlToBinary(*xmlState, destData);
  

}

void Karplus_finalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> theParams(getXmlFromBinary(data, sizeInBytes));
    if (theParams != nullptr)
    {
        if (theParams->hasTagName(parameters.state.getType()))
        {
            parameters.state = ValueTree::fromXml(*theParams);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Karplus_finalAudioProcessor();
}

//void Karplus_finalAudioProcessor::readAudioFile(AudioSampleBuffer& buffer, const void* data, size_t sizeBytes)
//{
//    WavAudioFormat wavFormat;
//    std::unique_ptr<AudioFormatReader> reader(wavFormat.createReaderFor(new MemoryInputStream(data, sizeBytes, false), true));
//    if (reader.get() != nullptr)
//    {
//        buffer.setSize(reader->numChannels, reader->lengthInSamples);
//        reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);
//    }
//    // reader is automatically deleted by using uique_ptr
//}


//void Karplus_finalAudioProcessor::readAudioFile(AudioSampleBuffer& buffer, const void* file, size_t fileSize)
//{
//    MemoryInputStream inputStream(file, fileSize, false);
//    WavAudioFormat wavFormat;
//    AudioFormatReader* reader = wavFormat.createReaderFor(&inputStream, false);
//    buffer.setSize(reader->numChannels, reader->lengthInSamples);
//    reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);
//}

