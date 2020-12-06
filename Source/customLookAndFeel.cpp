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
    //loading my image in
    setColour(Slider::thumbColourId, Colours::black);

    myDial = ImageFileFormat::loadFrom(BinaryData::dial_png, BinaryData::dial_pngSize);

}

void customLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider){
    //seting radius of circle as the minum of width and height
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

void customLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos,
    float minSliderPos,
    float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider)
{
    if (slider.isBar())
    {
        g.setColour(juce::Colour(122, 201, 67));
        g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), y + 0.5f, sliderPos - x, height - 1.0f)
            : Rectangle<float>(x + 0.5f, sliderPos, width - 1.0f, y + (height - sliderPos)));
    }
    else
    {
        auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = jmin(6.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

        Point<float> startPoint(slider.isHorizontal() ? x : x + width * 0.5f,
            slider.isHorizontal() ? y + height * 0.5f : height + y);

        Point<float> endPoint(slider.isHorizontal() ? width + x : startPoint.x,
            slider.isHorizontal() ? startPoint.y : y);

        Path backgroundTrack;
        backgroundTrack.startNewSubPath(startPoint);
        backgroundTrack.lineTo(endPoint);
        g.setColour(juce::Colour(122, 201, 67));
        g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::mitered, PathStrokeType::square });

        Path valueTrack;
        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
                         slider.isHorizontal() ? height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
                               slider.isHorizontal() ? height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
                         slider.isHorizontal() ? height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
            auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = getSliderThumbRadius(slider);

        valueTrack.startNewSubPath(minPoint);
        valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
        g.setColour(slider.findColour(Slider::trackColourId));
        g.strokePath(valueTrack, { trackWidth, PathStrokeType::mitered, PathStrokeType::square });

        if (!isTwoVal)
        {
            g.setColour(Colours::black);

            g.fillRect(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));

        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin(trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
            auto pointerColour = Colours::black;

            if (slider.isHorizontal())
            {
                drawPointer(g, minSliderPos - sr,
                    jmax(0.0f, y + height * 0.5f - trackWidth * 2.0f),
                    trackWidth * 2.0f, pointerColour, 2);

                drawPointer(g, maxSliderPos - trackWidth,
                    jmin(y + height - trackWidth * 2.0f, y + height * 0.5f),
                    trackWidth * 2.0f, pointerColour, 4);
            }
            else
            {
                drawPointer(g, jmax(0.0f, x + width * 0.5f - trackWidth * 2.0f),
                    minSliderPos - trackWidth,
                    trackWidth * 2.0f, pointerColour, 1);

                drawPointer(g, jmin(x + width - trackWidth * 2.0f, x + width * 0.5f), maxSliderPos - sr,
                    trackWidth * 2.0f, pointerColour, 3);
            }
        }
    }
}
