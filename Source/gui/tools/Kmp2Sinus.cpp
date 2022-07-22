/*
  ==============================================================================

    Kmp2Sinus.cpp
    Created: 11 Jul 2022 8:10:04pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "Kmp2Sinus.h"

void Kmp2Sinus::perform(juce::Point<float> startPoint, juce::Point<float> newPoint, juce::Path* path)
{
    juce::Rectangle<float> rectangle(startPoint, newPoint);
    
    juce::Point<float> controlPoint1(rectangle.getX(), rectangle.getY() + rectangle.getHeight() / 2);
    juce::Point<float> controlPoint2(rectangle.getX() + rectangle.getWidth() / 4, rectangle.getY());
    juce::Point<float> controlPoint3(rectangle.getX() + rectangle.getWidth() / 2, rectangle.getY() + rectangle.getHeight() / 2);
    juce::Point<float> controlPoint4(rectangle.getX() + rectangle.getWidth() / 4 * 3, rectangle.getY() + rectangle.getHeight());
    juce::Point<float> controlPoint5(rectangle.getX() + rectangle.getWidth(), rectangle.getY() + rectangle.getHeight() / 2);
    
    path->clear();
    path->startNewSubPath(controlPoint1);
    path->quadraticTo(controlPoint2, controlPoint3);
    path->quadraticTo(controlPoint4, controlPoint5);
}
