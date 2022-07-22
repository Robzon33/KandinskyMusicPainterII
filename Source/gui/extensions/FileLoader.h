/*
  ==============================================================================

    FileLoader.h
    Created: 20 Jul 2022 5:47:05pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../model/MainModel.h"

class FileLoader
{
public:
    /** Loads a KMP II file. */
    static void loadFile(std::unique_ptr<juce::XmlElement> element, MainModel&);
private:
    /** This is to prevent you from creating an instance. */
    FileLoader();
    
    /** Private functions to load different parts of the model. */
    static void loadModel(juce::XmlElement* element, MainModel& model);
    static void loadTrack(juce::XmlElement* element, MidiTrack& midiTrack);
    static void loadMidiData(juce::XmlElement* element, MidiTrack& midiTrack);
    static void loadMidiVelocityDat(juce::XmlElement* element, MidiVelocityData& midiVelocityData);
};
