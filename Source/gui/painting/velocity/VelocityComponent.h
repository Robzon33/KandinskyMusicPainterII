/*
  ==============================================================================

    VelocityComponent.h
    Created: 12 Jul 2022 4:39:47pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../../model/midi/MidiTrack.h"

class VelocityComponent  : public juce::Component
{
public:
    VelocityComponent(MidiTrack&);
    ~VelocityComponent();

    void paint (juce::Graphics&) override;
    void mouseDown(const juce::MouseEvent& event) override;
private:
    MidiTrack& midiTrack;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VelocityComponent)
};
