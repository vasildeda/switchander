#include "Logo.h"

Logo::Logo()
{
    vr_ = juce::Drawable::createFromImageData(BinaryData::vr_svg,
                                              BinaryData::vr_svgSize);
    switchander_ = juce::Drawable::createFromImageData(BinaryData::switchander_svg,
                                                       BinaryData::switchander_svgSize);
}

void Logo::paint(juce::Graphics& g)
{
    if (vr_)
        vr_->drawWithin(g, getLocalBounds().toFloat().reduced(4),
                         juce::RectanglePlacement::centred, 1.0f);
}
