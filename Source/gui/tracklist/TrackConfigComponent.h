/*
  ==============================================================================

    TrackConfigComponent.h
    Created: 11 Jul 2022 9:18:47pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/model/MainModel.h"
#include "../custom/PropertyComponents.h"

class TrackConfigComponent  :   public juce::Component,
                                public juce::ChangeBroadcaster,
                                public juce::TextPropertyComponent::Listener,
                                public juce::ChangeListener
{
public:
    TrackConfigComponent(MidiTrack&);
    ~TrackConfigComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void textPropertyComponentChanged(juce::TextPropertyComponent* component) override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    MidiTrack& track;
    std::unique_ptr<juce::PropertyPanel> propertyPanel;

    juce::TextPropertyComponent* nameComponent;
    SelectBooleanComponent* isVisibleComponent;
    SelectBooleanComponent* isAudibleComponent;
    ColourButtonPropertyComponent* colourComponent;
    SelectProgramComponent* programComponent;
    SelectChannelComponent* channelComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackConfigComponent)
};
