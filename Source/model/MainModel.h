/*
  ==============================================================================

    MainModel.h
    Created: 11 Jul 2022 3:53:20pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "midi/MidiTrack.h"

class MainModel
{
public:
    MainModel();
    ~MainModel();

    /** Sets a new project name. */
    void setProjectName(juce::String newProjectName);
    
    /** Returns the projects name. */
    juce::String getProjectName();
    
    /** Sets a new width. */
    void setWidth(int newWidth);
    
    /** Returns the projects width. */
    int getWidth();
    
    /** Returns the maximum number of midi tracks you can create for a single project. */
    int getMaxNumberOfMidiTracks();
    
    // ==============================================================================
    
    /** Adds a new midi track to the model. In case of the limit of midi tracks has already been
        reached, it returns false.
    */
    bool addMidiTrack();
    
    /** Returns the midi track for the given index. */
    MidiTrack* getMidiTrack(int index);
    
    /** Deletes the midi track at the given index. */
    void deleteTrack(int index);
    
    /** Deletes all midi tracks. */
    void deleteAllTracks();
    
    /** Returns the last tracks index. */
    int getIndexOfLastTrack();
    
    /** Returns the tracks name for a given index. */
    juce::String getTrackName(int index);
    
    /** Returns all midi tracks. Not used at the moment. Delete? */
    juce::Array<MidiTrack*> getAllTracks();
    
    /** Returns all midi tracks. */
    juce::OwnedArray<MidiTrack>& getMidiTracks();
    
    /** Returns the number of created midi tracks. */
    int getNumberOfTracks();
    
    /** Updates each tracks width. */
    void updateTrackWidth(int newWidth);
    
    /** Resets the model. */
    void reset();
private:
    juce::OwnedArray<MidiTrack> midiTracks;
    
    // project config params
    juce::String projectName;
    int width;
    const int maxNumberOfMidiTracks = 16;
};
