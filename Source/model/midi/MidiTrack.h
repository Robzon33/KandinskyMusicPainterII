/*
  ==============================================================================

    MidiTrack.h
    Created: 11 Jul 2022 3:53:46pm
    Author:  Tobias Koelker

    A MidiTrack contains the graphical objects, track configurations and MIDI
    data.
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "MidiVelocityData.h"

class MidiTrack
{
public:
    MidiTrack(int width);
    ~MidiTrack();
    
    //==========================================================================
    void addPath(juce::Path newPath);
    juce::Path& getPath(int index);
    juce::OwnedArray<juce::Path>& getPaths();
    void deletePath(int index);
    void deleteAllPaths();
    void movePath(int index, int x, int y);
    
    //==========================================================================
    void setChannel(int newChannel);
    int getChannel();
    void setProgram(int newProgram);
    int getProgram();
    void setColour(juce::Colour newColour);
    juce::Colour getColour();
    void setTrackName(juce::String newName);
    juce::String getTrackName();
    void setAudible(bool isAudible);
    bool isAudible();
    void setVisible(bool isVisible);
    bool isVisible();
    void setWidth(int newWidth);
    MidiVelocityData& getMidiVelocityData();
    
    int getNumberOfPaths();
    juce::Array<float> calculateIntersections(int x);
private:
    int channel, program;
    juce::OwnedArray<juce::Path> pathVector;
    juce::String trackName;
    juce::Colour trackColour;
    bool visible, audible;
    int width;
    std::unique_ptr<MidiVelocityData> midiVelocityData;
    
    juce::Colour generateRandomColour();
};
