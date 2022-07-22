/*
  ==============================================================================

    TrackComponent.h
    Created: 12 Jul 2022 4:39:26pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../../model/midi/MidiTrack.h"
#include "Drawer.h"

class TrackComponent : public juce::Component
{
public:
    TrackComponent(MidiTrack&, Drawer&);
    ~TrackComponent();

    void paint(juce::Graphics& g) override;

    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
private:
    MidiTrack& track;
    Drawer& drawer;

    /** Path you are currently drawing. */
    juce::Path cp;
};
