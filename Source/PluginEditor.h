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

        customLookAndFeel otherLookAndFeel;
};
