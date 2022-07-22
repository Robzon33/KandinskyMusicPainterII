/*
  ==============================================================================

    MainPaintingComponent.cpp
    Created: 11 Jul 2022 6:54:16pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "MainPaintingComponent.h"

MainPaintingComponent::MainPaintingComponent(MainModel& mm, MidiPlayer& mp, juce::ApplicationCommandManager& acm)
: model(mm), player(mp), commandManager(acm)
{
    paintingTextButton.reset(new juce::TextButton("Painting"));
    paintingTextButton->setToggleable(true);
    paintingTextButton->setClickingTogglesState(true);
    paintingTextButton->setToggleState(true, juce::dontSendNotification);
    paintingTextButton->addListener(this);
    paintingTextButton->setColour (juce::TextButton::textColourOffId,  juce::Colours::red);
    addAndMakeVisible(paintingTextButton.get());
    
    velocityTextButton.reset(new juce::TextButton("Velocity"));
    velocityTextButton->setToggleable(true);
    velocityTextButton->setClickingTogglesState(true);
    velocityTextButton->setToggleState(true, juce::dontSendNotification);
    velocityTextButton->addListener(this);
    velocityTextButton->setColour (juce::TextButton::textColourOffId,  juce::Colours::red);
    addAndMakeVisible(velocityTextButton.get());

    frameTrackComponent.reset(new FrameTrackComponent(model, player));
    addAndMakeVisible(frameTrackComponent.get());

    frameVelocityComponent.reset(new FrameVelocityComponent(model));
    addAndMakeVisible(frameVelocityComponent.get());
    
    this->setComponentSize();
}

MainPaintingComponent::~MainPaintingComponent()
{
    
}

void MainPaintingComponent::paint(juce::Graphics& g)
{
}

void MainPaintingComponent::resized()
{
    this->setComponentSize();
    
    auto b = getLocalBounds();
    
    paintingTextButton->setBounds(b.removeFromTop(this->textButtonHeight).reduced(5));
    
    if (frameTrackComponent->isVisible())
    {
        frameTrackComponent->setBounds(b.removeFromTop(this->frameTrackComponentHeight));
    }
    
    velocityTextButton->setBounds(b.removeFromTop(this->textButtonHeight).reduced(5));
    
    if (frameVelocityComponent->isVisible())
    {
        frameVelocityComponent->setBounds(b.removeFromTop(this->frameVelocityComponentHeight));
    }
}

void MainPaintingComponent::addTrackComponents(MidiTrack* newTrack)
{
    frameTrackComponent->addTrackComponent(newTrack);
    frameVelocityComponent->addVelocityComponent(newTrack);
}

void MainPaintingComponent::deleteTrackComponent (int index)
{
    frameTrackComponent->deleteTrackComponent (index);
    frameVelocityComponent->deleteVelocityComponent (index);
}

void MainPaintingComponent::deleteAllTrackComponents()
{
    frameTrackComponent->deleteAllTrackComponents();
    frameVelocityComponent->deleteAllVelocityComponents();
}

void MainPaintingComponent::setSelectedTool (int index)
{
    frameTrackComponent->setSelectedTool (index);
}

void MainPaintingComponent::setSelectedTrack (int index)
{
    frameTrackComponent->setSelectedTrack (index);
    frameVelocityComponent->setSelectedMidiVelocityData (index);
}

void MainPaintingComponent::buttonClicked(juce::Button* source)
{
    if (source == paintingTextButton.get())
    {
        frameTrackComponent->setVisible(paintingTextButton->getToggleState());
        resized();
    }
    if (source == velocityTextButton.get())
    {
        frameVelocityComponent->setVisible(velocityTextButton->getToggleState());
        resized();
    }
}

void MainPaintingComponent::setComponentSize()
{
    int height = textButtonHeight * 2;
    if (frameTrackComponent->isVisible())
    {
        height = height + frameTrackComponentHeight;
    }
    if (frameVelocityComponent->isVisible())
    {
        height = height + frameVelocityComponentHeight;
    }
    
    setSize(model.getWidth(), height);
}

void MainPaintingComponent::loadModel()
{
    frameTrackComponent->loadModel();
    frameVelocityComponent->loadModel();
}
