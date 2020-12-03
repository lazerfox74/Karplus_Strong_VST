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

#define DAMP_ID "damp"
#define DAMP_NAME "Dampening"

#define IMP_ID "impulse"
#define IMP_NAME "Impulse Filter"

#define STEREO_ID "stereo"
#define STEREO_NAME "Stereo"

#define PICK_ID "pick"
#define PICK_NAME "Pick"

#define FINGER_ID "pick"
#define FINGER_NAME "Pick"

#define STICK_ID "stick"
#define STICK_NAME "Stick"

#define BUTTON_ID "buttons"
#define BUTTON_NAME "Buttons"
//==============================================================================
/**
*/
class Karplus_finalAudioProcessorEditor  : public AudioProcessorEditor, private juce::Slider::Listener
{
public:
    Karplus_finalAudioProcessorEditor (Karplus_finalAudioProcessor&);
    ~Karplus_finalAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Karplus_finalAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Karplus_finalAudioProcessorEditor)


        ImageButton pickB, fingerB, stickB;
        
        Image backGround;

        enum impulseState
        {
            pick,
            finger,
            stick
        };

        void changeImpulse(impulseState impulse);

        Slider impulseFilterSlider, dampningSlider, stereoSlider;

        ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>dampAttatch;
        ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>impAttatch;
        ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>stereoAttatch;

        //ScopedPointer<AudioProcessorValueTreeState::Butt>buttonAttatch;
        //ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment>fingerAttatch;
        //ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment>stickAttatch;







        customLookAndFeel otherLookAndFeel;
};
