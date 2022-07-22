/*
  ==============================================================================

    Kmp2Ellipse.cpp
    Created: 11 Jul 2022 8:09:37pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "Kmp2Ellipse.h"

void Kmp2Ellipse::perform(juce::Point<float> startPoint, juce::Point<float> newPoint, juce::Path* path)
{
    float x = juce::jmin<float>(startPoint.getX(), newPoint.getX());
    float y = juce::jmin<float>(startPoint.getY(), newPoint.getY());
    float width = std::abs(startPoint.getX() - newPoint.getX());
    float height = std::abs(startPoint.getY() - newPoint.getY());
    
    path->clear();
    path->startNewSubPath(startPoint);
    path->addEllipse(x, y, width, height);
}
