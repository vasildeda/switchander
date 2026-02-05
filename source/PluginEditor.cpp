/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SwichanderAudioProcessorEditor::SwichanderAudioProcessorEditor(SwichanderAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor_(p)
{
    addAndMakeVisible(logo_);

    for (int i = 0; i < 5; ++i)
    {
        midiButtons_[i].setButtonText("--");
        midiButtons_[i].onClick = [this, i] {
            audioProcessor_.midiLearnTarget_.store(i, std::memory_order_relaxed);
        };
        addAndMakeVisible(midiButtons_[i]);
    }

    // Register callback for processor → GUI updates
    audioProcessor_.onMidiLearned = [this] {
        updateMidiButtons();
    };

    setSize(704, 396);
}

SwichanderAudioProcessorEditor::~SwichanderAudioProcessorEditor()
{
    audioProcessor_.onMidiLearned = nullptr;
}

void SwichanderAudioProcessorEditor::updateMidiButtons()
{
    // TODO: Display learned MIDI trigger info
}

//==============================================================================
void SwichanderAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void SwichanderAudioProcessorEditor::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    juce::Grid grid;
    grid.templateRows = { Track(Fr(1)), Track(Fr(1)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),
                             Track(Fr(1)), Track(Fr(1)) };

    grid.items = {
        juce::GridItem(logo_),
        juce::GridItem(),  // empty
        juce::GridItem(),  // empty
        juce::GridItem(),  // empty
        juce::GridItem(),  // empty
        juce::GridItem(midiButtons_[0]),
        juce::GridItem(midiButtons_[1]),
        juce::GridItem(midiButtons_[2]),
        juce::GridItem(midiButtons_[3]),
        juce::GridItem(midiButtons_[4])
    };

    grid.performLayout(getLocalBounds());
}
