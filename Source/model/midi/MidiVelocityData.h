/*
  ==============================================================================

    MidiVelocityData.h
    Created: 20 Jul 2022 12:15:37pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MidiVelocityData {
public:
    /** Constructor */
    MidiVelocityData(int width);

    /** Destructor */
    ~MidiVelocityData();

    /** Adds a point to the array. */
    void addPoint(int x, int y);
    
    /** Deletes a point. It is not possible to delete the first
        or last point. */
    void deletePoint(int index);

    /** Sets a new width. Some points might get deleted if the width
        gets less and thus they are out of bounds. */
    void updateWidth(int newWidth);

    /** Returns a list of all existing points. */
    juce::OwnedArray<juce::Point<int>>& getPointVector();

    /** Returns the index of a point from the pointVector. If
        you have not hit a point it returns -1. */
    int getIndexOfPoint(int x, int y);

    /** Returns a velocity for a given position. */
    int getVelocity(int x);
private:
    juce::OwnedArray<juce::Point<int>> pointVector;
    int width;
    const int maxNumberOfPoints = 20;
    const int defaultVelocityValue = 70;
};
