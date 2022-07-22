/*
  ==============================================================================

    FileLoader.cpp
    Created: 20 Jul 2022 5:47:05pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "FileLoader.h"

void FileLoader::loadFile(std::unique_ptr<juce::XmlElement> element, MainModel& model)
{
    juce::XmlElement* xmlModel = element->getChildByName("TRACKS");
    loadModel(xmlModel, model);
}

void FileLoader::loadModel(juce::XmlElement* element, MainModel& model)
{
    model.deleteAllTracks();

    int index = 0;

    for (auto* track : element->getChildIterator())
    {
        if (track->hasTagName("TRACK"))
        {
            if (model.addMidiTrack())
            {
                loadTrack(track, *model.getMidiTrack(index));
            }
        }
        index++;
    }
}

void FileLoader::loadTrack(juce::XmlElement* element, MidiTrack& midiTrack)
{
    if (element->hasAttribute("name"))
    {
        midiTrack.setTrackName(element->getStringAttribute("name"));
    }
    if (element->hasAttribute("colour"))
    {
        midiTrack.setColour(juce::Colour::fromString(element->getStringAttribute("colour")));
    }
    if (element->hasAttribute("audible"))
    {
        midiTrack.setAudible(element->getBoolAttribute("audible"));
    }
    if (element->hasAttribute("visible"))
    {
        midiTrack.setVisible(element->getBoolAttribute("visible"));
    }

    juce::XmlElement* xmlPaths = element->getChildByName("PATHS");
    if (xmlPaths->hasTagName("PATHS"))
    {
        for (auto* xmlPath : xmlPaths->getChildIterator())
        {
            if (xmlPath->hasTagName("Path"))
            {
                juce::Path p;
                p.restoreFromString(xmlPath->getStringAttribute("data"));
                midiTrack.addPath(p);
            }
        }
    }

    juce::XmlElement* xmlMidi = element->getChildByName("MIDIDATA");
    loadMidiData(xmlMidi, midiTrack);

    juce::XmlElement* xmlMidiVelocity = element->getChildByName("VELOCITY");
    loadMidiVelocityDat(xmlMidiVelocity, midiTrack.getMidiVelocityData());
}

void FileLoader::loadMidiData(juce::XmlElement* element, MidiTrack& midiTrack)
{
    if (element->hasAttribute("program"))
    {
        midiTrack.setProgram(element->getIntAttribute("program"));
    }
    if (element->hasAttribute("channel"))
    {
        midiTrack.setChannel(element->getIntAttribute("channel"));
    }
}

void FileLoader::loadMidiVelocityDat(juce::XmlElement* element, MidiVelocityData& midiVelocityData)
{
    for (auto* e : element->getChildIterator())
    {
        if (e->hasTagName("Point"))
        {
            midiVelocityData.addPoint(e->getIntAttribute("x"), e->getIntAttribute("y"));
        }
    }
}
