/*
  ==============================================================================

    Kmp2Rectangle.cpp
    Created: 11 Jul 2022 8:09:56pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "Kmp2Rectangle.h"

void Kmp2Rectangle::perform(juce::Point<float> startPoint, juce::Point<float> newPoint, juce::Path* path)
{
    float x = juce::jmin<float>(newPoint.getX(), startPoint.getX());
    float y = juce::jmin<float>(newPoint.getY(), startPoint.getY());
    float width = std::abs(newPoint.getX() - startPoint.getX());
    float height = std::abs(newPoint.getY() - startPoint.getY());
    
    path->clear();
    path->startNewSubPath(startPoint);
    path->addRectangle(x, y, width, height);
}
