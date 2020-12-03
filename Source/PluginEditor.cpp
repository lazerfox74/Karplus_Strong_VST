/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Karplus_finalAudioProcessorEditor::Karplus_finalAudioProcessorEditor (Karplus_finalAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);

    dampAttatch = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, DAMP_ID, dampningSlider);
    stereoAttatch = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, STEREO_ID, stereoSlider);
    impAttatch = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, IMP_ID, impulseFilterSlider);


    //setting up ui componenets
    Image fingerNP = ImageCache::getFromMemory(BinaryData::finger_png, BinaryData::finger_pngSize);
    Image fingerP = ImageCache::getFromMemory(BinaryData::finger_press_png, BinaryData::finger_press_pngSize);

    Image pickNP = ImageCache::getFromMemory(BinaryData::pick_png, BinaryData::pick_pngSize);
    Image pickP = ImageCache::getFromMemory(BinaryData::pick_press_png, BinaryData::pick_press_pngSize);

    Image stickNP = ImageCache::getFromMemory(BinaryData::stick_png, BinaryData::stick_pngSize);
    Image stickP = ImageCache::getFromMemory(BinaryData::stick_press_png, BinaryData::stick_press_pngSize);

    Image press = ImageCache::getFromMemory(BinaryData::press_png, BinaryData::press_pngSize);

    pickB.setLookAndFeel(&otherLookAndFeel);
    fingerB.setLookAndFeel(&otherLookAndFeel);
    stickB.setLookAndFeel(&otherLookAndFeel);



    pickB.setImages(false, true, true, pickNP, 1.0f, {},press , 1.0f, {}, pickP, 1.0f, {});
    addAndMakeVisible(pickB);
    pickB.onClick = [this] { changeImpulse(pick); };
    pickB.setClickingTogglesState(true);


    fingerB.setImages(false, true, true, fingerNP, 1.0f, {}, press, 1.0f, {}, fingerP, 1.0f, {});
    addAndMakeVisible(fingerB);
    fingerB.onClick = [this] { changeImpulse(finger); };
    fingerB.setClickingTogglesState(true);


    stickB.setImages(false, true, true, stickNP, 1.0f, {}, press, 1.0f, {}, stickP, 1.0f, {});
    addAndMakeVisible(stickB);
    stickB.onClick = [this] { changeImpulse(stick); };
    stickB.setClickingTogglesState(true);

    pickB.setRadioGroupId(5);
    fingerB.setRadioGroupId(5);
    stickB.setRadioGroupId(5);


    impulseFilterSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    dampningSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    stereoSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);

    impulseFilterSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    dampningSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    stereoSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);


    impulseFilterSlider.setLookAndFeel(&otherLookAndFeel);
    dampningSlider.setLookAndFeel(&otherLookAndFeel);
    stereoSlider.setLookAndFeel(&otherLookAndFeel);

    dampningSlider.setRange(0.01f, 10.0f);
    //dampningSlider.setSkewFactorFromMidPoint(f);
    dampningSlider.addListener(this);

    stereoSlider.setRange(1,1.3);
    stereoSlider.setSkewFactorFromMidPoint(1.05);
    stereoSlider.addListener(this);

    impulseFilterSlider.setRange(200, 15000);
    impulseFilterSlider.setSkewFactorFromMidPoint(5000);
    impulseFilterSlider.addListener(this);

    addAndMakeVisible(impulseFilterSlider);
    addAndMakeVisible(dampningSlider);
    addAndMakeVisible(stereoSlider);

    //impulseFilterSlider.setValue(processor.globalSettings.impulseFilt);
    //stereoSlider.setValue(processor.globalSettings.stereo);
    //dampningSlider.setValue(processor.globalSettings.dampning);



    backGround = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);



}

Karplus_finalAudioProcessorEditor::~Karplus_finalAudioProcessorEditor()
{
}

//==============================================================================
void Karplus_finalAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.setColour(Colours::white);

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);

    g.drawImageAt(backGround, 0, 0);
    //g.drawFittedText ("Exitor", getLocalBounds().removeFromTop(50), Justification::centred, 1);
}

void Karplus_finalAudioProcessorEditor::resized()
{

    //auto r = getLocalBounds();
    //r.removeFromTop(200);
    //auto topLeftSectoin = r.removeFromLeft(r.getWidth() / 2);
    //auto divisor = topLeftSectoin.getWidth() / 3;

    //pickB.setBounds(topLeftSectoin.removeFromRight(divisor));
    //fingerB.setBounds(topLeftSectoin.removeFromRight(divisor));
    //stickB.setBounds(topLeftSectoin);
    //
    //impulseFilterSlider.setBounds(r.removeFromLeft(divisor));
    //dampningSlider.setBounds(r.removeFromLeft(divisor));
    //stereoSlider.setBounds(r);

    //backGround.setBounds(0, 0, 600, 300);

    int xSpacing = getWidth()/6;

    pickB.setBounds(0, 100, 100, 100);
    fingerB.setBounds(xSpacing, 100, 100, 100);
    stickB.setBounds(xSpacing * 2, 100, 100, 100);

    impulseFilterSlider.setBounds(xSpacing * 3, 100, 100, 100);
    dampningSlider.setBounds(xSpacing * 4, 100, 100, 100);
    stereoSlider.setBounds(xSpacing * 5, 100, 100, 100);

}

void Karplus_finalAudioProcessorEditor::changeImpulse(impulseState impulse)
{
    switch(impulse)
    {
    case pick:

        pickB.setEnabled(false);
        fingerB.setEnabled(true);
        stickB.setEnabled(true);


        processor.globalSettings.impulse = 0;


        break;

    case finger:

        pickB.setEnabled(true);
        stickB.setEnabled(true);
        fingerB.setEnabled(false);
         
        processor.globalSettings.impulse = 1;
        //processor.ValueTree::setProperty(BUTTON_ID, 0.0f);
        break;

    case stick:

        stickB.setEnabled(false);
        fingerB.setEnabled(true);
        pickB.setEnabled(true);



        processor.globalSettings.impulse = 2;


        break;

    }
}

void Karplus_finalAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &dampningSlider)
    {
        processor.globalSettings.dampning = dampningSlider.getValue();
    }
    else if (slider == &stereoSlider)
    {
        processor.globalSettings.stereo = stereoSlider.getValue();
    }
    else if (slider == &impulseFilterSlider)
    {
        processor.globalSettings.impulseFilt = impulseFilterSlider.getValue();
    }

}

