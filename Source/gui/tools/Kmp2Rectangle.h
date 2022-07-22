/*
  ==============================================================================

    Kmp2Rectangle.h
    Created: 11 Jul 2022 8:09:56pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2Tool.h"

class Kmp2Rectangle : public Kmp2Tool
{
public:
    void perform(juce::Point<float> startPoint, juce::Point<float> newPoint, juce::Path* path) override;
};
