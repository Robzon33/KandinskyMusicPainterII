/*
  ==============================================================================

    MidiMonitorComponent.cpp
    Created: 22 Jul 2022 4:02:42pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "MidiMonitorComponent.h"

MidiMonitorComponent::MidiMonitorComponent(MidiPlayer& mp)
    :   midiPlayer (mp),
        midiMessageList (mp.getMidiMessageList()),
        midiLogListBoxModel (midiMessageList)
{
    midiPlayer.addChangeListener(this);

    outgoingMidiLabel.setText("Midi Messages", juce::NotificationType::dontSendNotification);
    outgoingMidiLabel.setFont(juce::Font(15.00f, juce::Font::plain));
    outgoingMidiLabel.setJustificationType(juce::Justification::centredLeft);
    outgoingMidiLabel.setEditable(false, false, false);
    outgoingMidiLabel.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    outgoingMidiLabel.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));
    addAndMakeVisible(outgoingMidiLabel);

    messageListBox.setModel(&midiLogListBoxModel);
    messageListBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0x32ffffff));
    messageListBox.setColour(juce::ListBox::outlineColourId, juce::Colours::black);
    messageListBox.setRowSelectedOnMouseDown(false);
    addAndMakeVisible(messageListBox);
}

MidiMonitorComponent::~MidiMonitorComponent()
{
}

void MidiMonitorComponent::paint(juce::Graphics&)
{
}

void MidiMonitorComponent::resized()
{
    auto area = this->getLocalBounds();

    outgoingMidiLabel.setBounds(area.removeFromTop(15));
    messageListBox.setBounds(area);
}

void MidiMonitorComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    messageListBox.updateContent();
    messageListBox.scrollToEnsureRowIsOnscreen(midiMessageList.size() - 1);
    messageListBox.repaint();
}
