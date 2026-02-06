#include "Logo.h"

Logo::Logo()
{
    vr_ = juce::Drawable::createFromImageData(BinaryData::vr_svg,
                                              BinaryData::vr_svgSize);

    switchander_ = juce::Drawable::createFromImageData(BinaryData::switchander_svg,
                                                       BinaryData::switchander_svgSize);
    switchander_->replaceColour(juce::Colour(0xffffffff), juce::Colours::red);
}

void Logo::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(4);

    if (switchander_)
    {
        auto swBounds = bounds.withTrimmedLeft(100).withTrimmedTop(50);
        switchander_->drawWithin(g, swBounds, juce::RectanglePlacement::xRight | juce::RectanglePlacement::yMid, 1.0f);
    }

    if (vr_)
    {
        auto vrBounds = bounds.reduced(bounds.getWidth() * 0.3f, bounds.getHeight() * 0.3f);
        vrBounds.setX(bounds.getX());
        auto cx = vrBounds.getCentreX();
        auto cy = vrBounds.getCentreY();

        g.saveState();
        g.addTransform(juce::AffineTransform::rotation(
            -juce::MathConstants<float>::pi / 6.0f, cx, cy));
        vr_->drawWithin(g, vrBounds, juce::RectanglePlacement::xLeft | juce::RectanglePlacement::yMid, 1.0f);
        g.restoreState();
    }
}
