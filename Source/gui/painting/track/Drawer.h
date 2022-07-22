/*
  ==============================================================================

    Drawer.h
    Created: 12 Jul 2022 9:55:20pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../tools/Kmp2Tool.h"

class Drawer
{
public:
    Drawer();
    ~Drawer();
    
    /** Sets the tool you want to use. */
    void setSelectedTool(int index);
    
    /** Draws an object to the current track component. */
    void draw(float x, float y, juce::Path* path);
    
    /** Resets the startPoint. */
    void reset();
private:
    std::unique_ptr<Kmp2Tool> kmp2tool;
    
    /** Remember where you have started drawing. */
    juce::Point<float> startPoint;
};
