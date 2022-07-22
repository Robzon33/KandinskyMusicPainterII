/*
  ==============================================================================

    TrackConfigComponent.cpp
    Created: 11 Jul 2022 9:18:48pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "TrackConfigComponent.h"

//==============================================================================
TrackConfigComponent::TrackConfigComponent(MidiTrack& mt)
    : track (mt)
{
    juce::Array<juce::PropertyComponent*> comps;

    nameComponent = new juce::TextPropertyComponent(juce::Value (track.getTrackName()), "Track Name", 200, false);
    nameComponent->addListener(this);
    comps.add(nameComponent);

    isVisibleComponent = new SelectBooleanComponent("Visible", track.isVisible());
    isVisibleComponent->addChangeListener(this);
    comps.add(isVisibleComponent);

    isAudibleComponent = new SelectBooleanComponent("Audible", track.isAudible());
    isAudibleComponent->addChangeListener(this);
    comps.add(isAudibleComponent);

    colourComponent = new ColourButtonPropertyComponent("Colour", track.getColour());
    colourComponent->addChangeListener(this);
    comps.add(colourComponent);

    programComponent = new SelectProgramComponent("Program Number", track.getProgram());
    programComponent->addChangeListener(this);
    comps.add(programComponent);

    channelComponent = new SelectChannelComponent("Channel", track.getChannel());
    channelComponent->addChangeListener(this);
    comps.add(channelComponent);

    propertyPanel.reset(new juce::PropertyPanel());
    propertyPanel->addProperties(comps);
    addAndMakeVisible(propertyPanel.get());
}

TrackConfigComponent::~TrackConfigComponent()
{
}

void TrackConfigComponent::paint (juce::Graphics& g)
{
    ///* This demo code just fills the component's background and
    //   draws some placeholder text to get you started.

    //   You should replace everything in this method with your own
    //   drawing code..
    //*/

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (juce::Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("TrackConfigComponent", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text
}

void TrackConfigComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> area(getLocalBounds().reduced(10));

    propertyPanel->setBounds(area);
}

void TrackConfigComponent::textPropertyComponentChanged(juce::TextPropertyComponent* component)
{
    if (component == nameComponent)
    {
        track.setTrackName(nameComponent->getText());
        this->sendChangeMessage();
    }
}

void TrackConfigComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == colourComponent)
    {
        track.setColour(colourComponent->getNewColour());
        sendChangeMessage();
    }
    if (source == programComponent)
    {
        track.setProgram(programComponent->getIndex());
    }
    if (source == isVisibleComponent)
    {
        track.setVisible(isVisibleComponent->getState());
        sendChangeMessage();
    }
    if (source == isAudibleComponent)
    {
        track.setAudible(isAudibleComponent->getState());
    }
    if (source == channelComponent)
    {
        track.setChannel(channelComponent->getChannel());
    }
}
