/*
  ==============================================================================

    FrameTrackComponent.cpp
    Created: 12 Jul 2022 4:39:16pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "FrameTrackComponent.h"

FrameTrackComponent::FrameTrackComponent(MainModel& m, MidiPlayer& mp)
    : model (m), player (mp)
{
    drawer.reset (new Drawer());
    showGrid = true;
    player.addChangeListener (this);
}

FrameTrackComponent::~FrameTrackComponent()
{
    
}

void FrameTrackComponent::paint(juce::Graphics& g)
{
    if (showGrid)
    {
        g.setColour(juce::Colours::black);
        for (int i = 100; i <= this->getWidth(); i = i + 100)
        {
            g.drawVerticalLine(i, 0.0f, (float) getHeight());
        }
    }
    
    // draw the players position.
    if (player.getPosition() > 0)
        {
            g.setColour(juce::Colours::blue);
            g.drawLine((float)player.getPosition(), 0, (float)player.getPosition(), getHeight(), 1);
        }
}

void FrameTrackComponent::resized()
{
    auto b = getLocalBounds();
    
    for (auto* trackComponent : tracks)
    {
        trackComponent->setBounds(b);
    }
}

void FrameTrackComponent::changeListenerCallback (juce::ChangeBroadcaster*)
{
    repaint();
}

void FrameTrackComponent::setSelectedTrack(int index)
{
    this->tracks[index]->toFront(true);
}

void FrameTrackComponent::addTrackComponent(MidiTrack* newTrack)
{
    TrackComponent* newTrackComponent = new TrackComponent(*newTrack, *drawer);
    addAndMakeVisible(newTrackComponent);
    newTrackComponent->setBounds(getLocalBounds());
    tracks.add(newTrackComponent);
}

void FrameTrackComponent::deleteTrackComponent(int index)
{
    tracks.remove(index);
}

void FrameTrackComponent::deleteAllTrackComponents()
{
    tracks.clear(true);
}

void FrameTrackComponent::setSelectedTool(int index)
{
    drawer->setSelectedTool(index);
}

void FrameTrackComponent::loadModel()
{
    this->tracks.clear();
    for (auto* track : model.getAllTracks())
    {
        this->addTrackComponent(track);
    }
}
