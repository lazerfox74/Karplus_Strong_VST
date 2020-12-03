/*
  ==============================================================================

    customLookAndFeel.h
    Created: 30 Nov 2020 8:39:17pm
    Author:  josh

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class customLookAndFeel : public LookAndFeel_V4
{
public:
    customLookAndFeel();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override;

    void drawImageButton(Graphics&, Image*, int imageX, int imageY, int imageW, int imageH, const Colour& overlayColour, float imageOpacity, ImageButton&)override;

private:

    Image myDial;

};