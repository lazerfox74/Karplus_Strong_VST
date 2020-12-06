/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "customLookAndFeel.h"

//defining the IDs for my user interface components
#define DAMP_ID "damp"
#define DAMP_NAME "Dampening"

#define IMP_ID "impulse"
#define IMP_NAME "Impulse Filter"

#define STEREO_ID "stereo"
#define STEREO_NAME "Stereo"

#define PICK_ID "pick"
#define PICK_NAME "Pick"

#define FINGER_ID "finger"
#define FINGER_NAME "Finger"

#define STICK_ID "stick"
#define STICK_NAME "Stick"

#define BUTTON_ID "buttons"
#define BUTTON_NAME "Buttons"

#define FREQDAMP_ID "freqDamp"
#define FREQDAMP_NAME "Frequency Dampening"

#define NOISEFILT_ID "noiseFilt"
#define NOISEFILT_NAME "Noise Filt"

//defining slider and button types to make code more compact

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
/**
*/
class Karplus_finalAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    //feeding in references to the audio processor and audioprocessor value tree state for acces to the values they contain
    Karplus_finalAudioProcessorEditor (Karplus_finalAudioProcessor&,juce::AudioProcessorValueTreeState& vts);
    ~Karplus_finalAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;


private:

    
    Karplus_finalAudioProcessor& processor;
    //reference to value tree state variable that can be set to the value tree state in the plugin processor in the constructor
    juce::AudioProcessorValueTreeState& valueTreeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Karplus_finalAudioProcessorEditor)

        //UI images
        ImageButton pickB, fingerB, stickB;
        
        Image backGround;
  
        //enums for chanign the state of my selected impulse
        enum impulseState
        {
            pick,
            finger,
            stick
        };
        //function to be called when impulse button is pressed
        void changeImpulse(impulseState impulse);
        //user interface sliders
        Slider impulseFilterSlider, dampningSlider, stereoSlider,freqDampSlider;
        //attatchments for attatching my audio processor tree values to my sliders
        ScopedPointer<SliderAttachment>dampAttatch, noiseFiltAttatch, stereoAttatch, freqDampAttatch;
        //attatchments for attatching my audio processor tree values to my buttons
        ScopedPointer<ButtonAttachment>pickAttatch, fingerAttatch, stickAttatch;
        //my custom ook and feel class
        customLookAndFeel otherLookAndFeel;
};
