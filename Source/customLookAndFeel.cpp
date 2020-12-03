/*
  ==============================================================================

    customLookAndFeel.cpp
    Created: 30 Nov 2020 8:39:17pm
    Author:  josh

  ==============================================================================
*/

#include "customLookAndFeel.h"

customLookAndFeel::customLookAndFeel()
{
    setColour(Slider::rotarySliderOutlineColourId, Colours::green);
    setColour(Slider::thumbColourId, Colours::black);
    setColour(Slider::rotarySliderFillColourId, Colours::blue);

    myDial = ImageFileFormat::loadFrom(BinaryData::dial_png, BinaryData::dial_pngSize);

}

void customLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider){

    int radius = jmin(width, height);
    int centreX = int(width / 2);
    int centreY = int(height / 2);
    float ventilCentreX = float(myDial.getWidth()) * .5f;
    float ventilCentreY = float(myDial.getHeight()) * .5f;
    float rotation = (MathConstants<float>::twoPi - MathConstants<float>::twoPi / 4) * sliderPos;

    myDial = myDial.rescaled(radius, radius, Graphics::ResamplingQuality::highResamplingQuality);

    AffineTransform transform;
    float centreImage = float(centreX) - ventilCentreX;

    transform = transform.rotation(rotation, ventilCentreX, ventilCentreY).translated(centreImage, 0);
    g.drawImageTransformed(myDial, transform, false);
}


void customLookAndFeel::drawImageButton(Graphics& g, Image* image,
    int imageX, int imageY, int imageW, int imageH,
    const Colour& overlayColour,
    float imageOpacity,
    ImageButton& button)
{
    //if (!button.isEnabled())
    //    imageOpacity *= 0.3f;

    AffineTransform t = RectanglePlacement(RectanglePlacement::stretchToFit)
        .getTransformToFit(image->getBounds().toFloat(),
            Rectangle<int>(imageX, imageY, imageW, imageH).toFloat());

    if (!overlayColour.isOpaque())
    {
        g.setOpacity(imageOpacity);
        g.drawImageTransformed(*image, t, false);
    }

    if (!overlayColour.isTransparent())
    {
        g.setColour(overlayColour);
        g.drawImageTransformed(*image, t, true);
    }
}
