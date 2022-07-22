/*
  ==============================================================================

    TextComponent.h
    Created: 12 Jul 2022 2:18:59pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class TextComponent : public juce::Component
{
public:
    TextComponent(juce::String text)
    {
        this->title = text;
    };

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::darkgrey);
        g.setColour(juce::Colours::orange);
        g.drawText("  " + title, getLocalBounds(), juce::Justification::centred, false);
    };
private:
    juce::String title;
};
