/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Karplus_finalAudioProcessorEditor::Karplus_finalAudioProcessorEditor (Karplus_finalAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 225);

    //setting up ui componenets
    Image fingerNP = ImageCache::getFromMemory(BinaryData::finger_png, BinaryData::finger_pngSize);
    Image fingerP = ImageCache::getFromMemory(BinaryData::finger_press_png, BinaryData::finger_press_pngSize);

    Image pickNP = ImageCache::getFromMemory(BinaryData::pick_png, BinaryData::pick_pngSize);
    Image pickP = ImageCache::getFromMemory(BinaryData::pick_press_png, BinaryData::pick_press_pngSize);

    Image stickNP = ImageCache::getFromMemory(BinaryData::stick_png, BinaryData::stick_pngSize);
    Image stickP = ImageCache::getFromMemory(BinaryData::stick_press_png, BinaryData::stick_press_pngSize);

    Image press = ImageCache::getFromMemory(BinaryData::press_png, BinaryData::press_pngSize);

    //setting up my image buttons
    pickAttatch.reset(new ButtonAttachment(valueTreeState, PICK_ID, pickB));
    fingerAttatch.reset(new ButtonAttachment(valueTreeState, FINGER_ID, fingerB));
    stickAttatch.reset(new ButtonAttachment(valueTreeState, STICK_ID, stickB));
    
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

    //setting up my sliders

    freqDampAttatch.reset(new SliderAttachment(valueTreeState, FREQDAMP_ID, freqDampSlider));
    freqDampSlider.setLookAndFeel(&otherLookAndFeel);
    freqDampSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    freqDampSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(freqDampSlider);

    noiseFiltAttatch.reset(new SliderAttachment(valueTreeState, NOISEFILT_ID, impulseFilterSlider));
    impulseFilterSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    impulseFilterSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    impulseFilterSlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(impulseFilterSlider);

    dampAttatch.reset(new SliderAttachment(valueTreeState, DAMP_ID, dampningSlider));
    dampningSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    dampningSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    dampningSlider.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(dampningSlider);

    stereoAttatch.reset(new SliderAttachment(valueTreeState, STEREO_ID, stereoSlider));
    stereoSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    stereoSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    stereoSlider.setLookAndFeel(&otherLookAndFeel);
    stereoSlider.setSkewFactorFromMidPoint(1.05);
    addAndMakeVisible(stereoSlider);


    //background image
    backGround = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);



}

Karplus_finalAudioProcessorEditor::~Karplus_finalAudioProcessorEditor()
{
}

//==============================================================================
void Karplus_finalAudioProcessorEditor::paint (Graphics& g)
{
    g.setColour(Colours::white);

    g.fillAll (Colours::white);

    g.drawImageAt(backGround, 0, 0);
}

void Karplus_finalAudioProcessorEditor::resized()
{

    int xSpacing = getWidth()/6;

    pickB.setBounds(0, 100, 100, 100);
    fingerB.setBounds(xSpacing, 100, 100, 100);
    stickB.setBounds(xSpacing * 2, 100, 100, 100);

    impulseFilterSlider.setBounds(xSpacing * 3, 100, 100, 100);
    dampningSlider.setBounds(xSpacing * 4, 100, 100, 100);
    stereoSlider.setBounds(xSpacing * 5, 100, 100, 100);
    freqDampSlider.setBounds(450, 200, 150, 25);

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
        break;

    case stick:

        stickB.setEnabled(false);
        fingerB.setEnabled(true);
        pickB.setEnabled(true);



        processor.globalSettings.impulse = 2;


        break;

    }
}

