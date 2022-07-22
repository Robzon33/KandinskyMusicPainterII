/*
  ==============================================================================

    FileSaver.h
    Created: 20 Jul 2022 5:46:56pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../model/MainModel.h"

class FileSaver
{
public:
    /** Converts a KMP II project to a xml document. */
    static juce::String convertProjectToXML(MainModel&);
private:
    /** This is to prevent you from creating an instance. */
    FileSaver();

    /** Converts a track to xml elements and adds it to a given xml element. */
    static void convertMidiTrackData(juce::XmlElement& element, MidiTrack* midiTrack);
};
