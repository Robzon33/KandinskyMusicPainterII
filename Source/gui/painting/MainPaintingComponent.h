/*
  ==============================================================================

    MainPaintingComponent.h
    Created: 11 Jul 2022 6:54:16pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../custom/TextComponent.h"
#include "track/FrameTrackComponent.h"
#include "velocity/FrameVelocityComponent.h"

#include "../../model/MainModel.h"
#include "../../player/MidiPlayer.h"

class MainPaintingComponent :   public 	juce::Component,
public juce::Button::Listener
{
public:
    MainPaintingComponent (MainModel&, MidiPlayer&, juce::ApplicationCommandManager&);
    ~MainPaintingComponent();
    
    void paint (juce::Graphics& g) override;
    void resized() override;
    
    void addTrackComponents (MidiTrack* newTrack);
    void deleteTrackComponent (int index);
    void deleteAllTrackComponents();
    
    void setSelectedTool (int index);
    void setSelectedTrack (int index);
    
    void buttonClicked (juce::Button* source) override;
    
    void loadModel();
private:
    MainModel& model;
    MidiPlayer& player;
    juce::ApplicationCommandManager& commandManager;

    std::unique_ptr<FrameTrackComponent> frameTrackComponent;
    std::unique_ptr<FrameVelocityComponent> frameVelocityComponent;
    
    std::unique_ptr<juce::TextButton> paintingTextButton;
    std::unique_ptr<juce::TextButton> velocityTextButton;
    
    void setComponentSize();
    
    /** Layout constants */
    const int textButtonHeight = 40;
    const int frameTrackComponentHeight = 127;
    const int frameVelocityComponentHeight = 127;
};
