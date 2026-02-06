#pragma once

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "BinaryData.h"

//==============================================================================
class Logo : public juce::Component
{
public:
    Logo();

    void paint(juce::Graphics& g) override;

private:
    std::unique_ptr<juce::Drawable> vr_;
    std::unique_ptr<juce::Drawable> switchander_;
};
