/*
  ==============================================================================

    Kmp2Tool.h
    Created: 11 Jul 2022 8:13:29pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Kmp2ToolIDs.h"

class Kmp2Tool
{
public:
    /** Virtual Destructor */
    virtual ~Kmp2Tool() {};

    /** Creates an instance of a KMP2 Tool. */
    static Kmp2Tool* Create(Kmp2ToolIDs toolID);

    /** Returns the number of supported Tools. */
    static int getNumberOfTools();

    /** Provides a button for each supported Tool. */
    static juce::DrawableButton* getButton(int index);
    
    /** Performs an action to the given path. */
    virtual void perform(juce::Point<float> startPoint,
                         juce::Point<float> newPoint,
                         juce::Path* path) = 0;
};
