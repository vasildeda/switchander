/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "Logo.h"
#include "LongPressButton.h"
#include "PluginProcessor.h"

//==============================================================================
class SwitchanderAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SwitchanderAudioProcessorEditor(SwitchanderAudioProcessor&);
    ~SwitchanderAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    SwitchanderAudioProcessor& audioProcessor_;

    Logo logo_;
    std::array<LongPressButton, 5> channelButtons_;

    void updateChannelButtons();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SwitchanderAudioProcessorEditor)
};
