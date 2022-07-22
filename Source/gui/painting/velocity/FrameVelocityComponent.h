/*
  ==============================================================================

    FrameVelocityComponent.h
    Created: 12 Jul 2022 4:39:37pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../../model/MainModel.h"
#include "VelocityComponent.h"

class FrameVelocityComponent : public juce::Component
{
public:
    FrameVelocityComponent(MainModel&);
    ~FrameVelocityComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setSelectedMidiVelocityData(int index);
    void addVelocityComponent(MidiTrack* newMidiTrack);
    void deleteVelocityComponent(int index);
    void deleteAllVelocityComponents();
    
    void loadModel();
private:
    MainModel& model;

    juce::OwnedArray<VelocityComponent> velocities;
    bool showGrid;
};
