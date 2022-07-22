/*
  ==============================================================================

    FrameTrackComponent.h
    Created: 12 Jul 2022 4:39:16pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../../model/MainModel.h"
#include "../../../player/MidiPlayer.h"
#include "TrackComponent.h"
#include "Drawer.h"

class FrameTrackComponent   : public juce::Component,
                              private juce::ChangeListener
{
public:
    FrameTrackComponent(MainModel& m, MidiPlayer& mp);
    ~FrameTrackComponent();
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void changeListenerCallback (juce::ChangeBroadcaster*) override;
    
    void setSelectedTrack(int index);
    void addTrackComponent(MidiTrack* newTrack);
    void deleteTrackComponent(int index);
    void deleteAllTrackComponents();
    
    void setSelectedTool(int index);
    
    void loadModel();
private:
    MainModel& model;
    MidiPlayer& player;
    bool showGrid;
    juce::OwnedArray<TrackComponent> tracks;
    std::unique_ptr<Drawer> drawer;
};
