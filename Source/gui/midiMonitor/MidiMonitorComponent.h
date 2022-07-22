/*
  ==============================================================================

    MidiMonitorComponent.h
    Created: 22 Jul 2022 4:02:42pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../player/MidiPlayer.h"

class MidiMonitorListBoxModel : public juce::ListBoxModel
{
public:
    MidiMonitorListBoxModel(juce::OwnedArray<juce::MidiMessage>& list)
        : midiMessageList(list)
    {
    }

    int getNumRows() override { return midiMessageList.size(); }

    void paintListBoxItem(int row, juce::Graphics& g, int width, int height, bool rowIsSelected) override
    {
        if (juce::isPositiveAndBelow(row, midiMessageList.size()))
        {
            g.setColour(juce::Colours::red);

            const juce::MidiMessage& message = *(midiMessageList[row]);
            if (message.isNoteOff())        { g.setColour(juce::Colours::blue.withAlpha(0.1f)); }
            if (message.isNoteOn())         { g.setColour(juce::Colours::blue.withAlpha(0.2f)); }
            if (message.isProgramChange())  { g.setColour(juce::Colours::blue.withAlpha(0.3f)); }

            g.fillAll();
            
            // The time stamp is the position in pixel when the midi message was sent.
            double timeStamp = message.getTimeStamp();
            
            g.setColour(juce::Colours::black);
            g.drawText(juce::String(timeStamp)
                       + "  -  " + message.getDescription(),
                       juce::Rectangle<int>(width, height).reduced(4, 0),
                       juce::Justification::centredLeft, true);
        }
    }

private:
    juce::OwnedArray<juce::MidiMessage>& midiMessageList;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiMonitorListBoxModel)
};

class MidiMonitorComponent : public juce::Component,
                             public juce::ChangeListener
{
public:
    MidiMonitorComponent(MidiPlayer&);
    ~MidiMonitorComponent();

    void paint(juce::Graphics&) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    MidiPlayer& midiPlayer;
    juce::Label outgoingMidiLabel;
    juce::ListBox messageListBox;
    juce::OwnedArray<juce::MidiMessage>& midiMessageList;
    MidiMonitorListBoxModel midiLogListBoxModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiMonitorComponent)
};
