/*
  ==============================================================================

    Kmp2Line.cpp
    Created: 11 Jul 2022 8:09:47pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "Kmp2Line.h"

void Kmp2Line::perform(juce::Point<float> startPoint, juce::Point<float> newPoint, juce::Path* path)
{
    path->clear();
    path->startNewSubPath(startPoint);
    path->lineTo(newPoint);
}
