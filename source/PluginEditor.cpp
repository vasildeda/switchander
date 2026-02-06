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
        channelButtons_[i].setText("--");
        channelButtons_[i].onClick = [this, i] {
            audioProcessor_.selectBus(i);
        };
        channelButtons_[i].onLongPress = [this, i] {
            audioProcessor_.midiLearnTarget_.store(i, std::memory_order_relaxed);
            updateChannelButtons();
        };
        addAndMakeVisible(channelButtons_[i]);
    }

    // Register callback for processor → GUI updates
    audioProcessor_.onStateChanged = [this] {
        updateChannelButtons();
    };

    // Initial state
    updateChannelButtons();

    setSize(704, 396);
}

SwichanderAudioProcessorEditor::~SwichanderAudioProcessorEditor()
{
    audioProcessor_.onStateChanged = nullptr;
}

void SwichanderAudioProcessorEditor::updateChannelButtons()
{
    int selectedBus = audioProcessor_.selectedBus_.load(std::memory_order_relaxed);
    int learningBus = audioProcessor_.midiLearnTarget_.load(std::memory_order_relaxed);

    for (int i = 0; i < 5; ++i)
    {
        channelButtons_[i].setSelected(i == selectedBus);
        channelButtons_[i].setLearning(i == learningBus);

        // Update text based on trigger assignment
        int32_t trigger = audioProcessor_.getMidiTrigger(i);
        if (trigger < 0)
        {
            channelButtons_[i].setText("--");
        }
        else
        {
            // Display as hex for now (status:data1)
            int status = (trigger >> 8) & 0xFF;
            int data1 = trigger & 0xFF;
            channelButtons_[i].setText(juce::String::toHexString(status) + ":" +
                                       juce::String::toHexString(data1));
        }
    }
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
        juce::GridItem(logo_).withColumn({ 2, 5 }).withRow({ 1, 2 }),  // span columns 2-4
        juce::GridItem(channelButtons_[0]).withColumn({ 1, 2 }).withRow({ 2, 3 }),
        juce::GridItem(channelButtons_[1]).withColumn({ 2, 3 }).withRow({ 2, 3 }),
        juce::GridItem(channelButtons_[2]).withColumn({ 3, 4 }).withRow({ 2, 3 }),
        juce::GridItem(channelButtons_[3]).withColumn({ 4, 5 }).withRow({ 2, 3 }),
        juce::GridItem(channelButtons_[4]).withColumn({ 5, 6 }).withRow({ 2, 3 })
    };

    grid.performLayout(getLocalBounds());
}
