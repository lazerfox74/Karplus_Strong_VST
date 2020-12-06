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
    //feeding my audioprocessorValueTree tree all the relevant UI values before my constructor
    parameters(*this, nullptr, juce::Identifier("easyNoise"),
        {
            std::make_unique<juce::AudioParameterFloat>(DAMP_ID,     // parameterID
                                                        DAMP_NAME,   // parameter name
                                                         0.01f,              // minimum value
                                                         10.0f,              // maximum value
                                                         5.0f),             // default value
            std::make_unique<juce::AudioParameterFloat>(STEREO_ID,      // parameterID
                                                        STEREO_NAME,    // parameter name
                                                         1.0f,
                                                         1.1f,
                                                         1.0f),             // default value
            std::make_unique<juce::AudioParameterFloat>(NOISEFILT_ID,      // parameterID
                                                        NOISEFILT_NAME,    // parameter name
                                                         200.0f,
                                                         15000.0f,
                                                         500.0f),             // default value
            std::make_unique<juce::AudioParameterFloat>(FREQDAMP_ID,      // parameterID
                                                      FREQDAMP_NAME,    // parameter name
                                                         0.1f,
                                                         0.99f,
                                                         0.4f),             // default value
            std::make_unique<juce::AudioParameterBool>(PICK_ID,      // parameterID
                                                       PICK_NAME,     // parameter name
                                                       false),              // default value
            std::make_unique<juce::AudioParameterBool>(FINGER_ID,      // parameterID
                                                       FINGER_NAME,     // parameter name
                                                       false),
            std::make_unique<juce::AudioParameterBool>(STICK_ID,      // parameterID
                                                       STICK_NAME,     // parameter name
                                                       true),

        })
#endif
{
    //setting the pointers in my settings object to the relevent controlls  
    globalSettings.dampPointer = parameters.getRawParameterValue(DAMP_ID);
    globalSettings.stereoPointer = parameters.getRawParameterValue(STEREO_ID);
    globalSettings.impulseFiltPointer = parameters.getRawParameterValue(NOISEFILT_ID);
    globalSettings.freqDampPointer = parameters.getRawParameterValue(FREQDAMP_ID);

    globalSettings.pickPointer = parameters.getRawParameterValue(PICK_ID);
    globalSettings.fingerPointer = parameters.getRawParameterValue(FINGER_ID);
    globalSettings.stickPointer = parameters.getRawParameterValue(STICK_ID);

    synth.clearVoices();
    //giving my synth 8 voices
    for (int i = 0; i < 8; ++i)
    {
        //sending reference to my settings so each voice can access the synth settings
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

    //clearing noise for good
    //for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear (i, 0, buffer.getNumSamples());

    //method for rendering audio in each of my voices
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples()); // [5]
}

//==============================================================================
bool Karplus_finalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Karplus_finalAudioProcessor::createEditor()
{
    return new Karplus_finalAudioProcessorEditor (*this,parameters);
}

//==============================================================================
void Karplus_finalAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    //sending the values of my audioProcessorValueTreeState to be stored as an XML File
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);

}

void Karplus_finalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //setting my AudioProcessorValueTreeState to the XML File Stored in Memory
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Karplus_finalAudioProcessor();
}


