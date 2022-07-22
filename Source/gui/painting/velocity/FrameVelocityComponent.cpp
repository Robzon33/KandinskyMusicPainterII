/*
  ==============================================================================

    FrameVelocityComponent.cpp
    Created: 12 Jul 2022 4:39:37pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "FrameVelocityComponent.h"

FrameVelocityComponent::FrameVelocityComponent(MainModel& m)
:model(m)
{
    this->showGrid = true;
}

FrameVelocityComponent::~FrameVelocityComponent()
{
}

void FrameVelocityComponent::paint(juce::Graphics& g)
{
    if (showGrid)
    {
        g.setColour(juce::Colours::black);
        for (int i = 100; i <= this->getWidth(); i = i + 100)
        {
            g.drawVerticalLine(i, 0.0f, (float) this->getHeight());
        }
    }
}

void FrameVelocityComponent::resized()
{
    auto b = getLocalBounds();
    
    for (auto* velocityComponent : velocities)
    {
        velocityComponent->setBounds(b);
    }
}

void FrameVelocityComponent::setSelectedMidiVelocityData(int index)
{
    this->velocities[index]->toFront(true);
}

void FrameVelocityComponent::addVelocityComponent(MidiTrack* newMidiTrack)
{
    VelocityComponent* newVelocityComponent = new VelocityComponent(*newMidiTrack);
    addAndMakeVisible(newVelocityComponent);
    newVelocityComponent->setBounds(getLocalBounds());
    velocities.add(newVelocityComponent);
}

void FrameVelocityComponent::deleteVelocityComponent(int index)
{
    velocities.remove(index);
}

void FrameVelocityComponent::deleteAllVelocityComponents()
{
    velocities.clear(true);
}

void FrameVelocityComponent::loadModel()
{
    this->velocities.clear(true);
    for (auto* track : model.getAllTracks())
    {
        addVelocityComponent(track);
    }
}
