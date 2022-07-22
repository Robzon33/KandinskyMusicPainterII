/*
  ==============================================================================

    Kmp2Ellipse.h
    Created: 11 Jul 2022 8:09:37pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2Tool.h"

class Kmp2Ellipse : public Kmp2Tool
{
public:
    void perform(juce::Point<float> startPoint, juce::Point<float> newPoint, juce::Path* path) override;
};
