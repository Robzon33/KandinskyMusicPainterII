/*
  ==============================================================================

    Kmp2Trail.cpp
    Created: 11 Jul 2022 8:10:14pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "Kmp2Trail.h"

void Kmp2Trail::perform(juce::Point<float> startPoint, juce::Point<float> newPoint, juce::Path* path)
{
    juce::Path newSegment;
    
    if (path->isEmpty())
    {
        newSegment.startNewSubPath(startPoint);
    }
    else
    {
        newSegment.startNewSubPath(path->getCurrentPosition().getX(), path->getCurrentPosition().getY());
    }
    newSegment.lineTo(newPoint);
    path->addPath(newSegment);
}
