/*
  ==============================================================================

    FileSaver.cpp
    Created: 20 Jul 2022 5:46:56pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "FileSaver.h"

juce::String FileSaver::convertProjectToXML(MainModel& mainModel)
{
    juce::String xmlDoc;
    juce::XmlElement project("KMP2PROJECT");

    // save settings
    juce::XmlElement* settings = new juce::XmlElement("SETTINGS");
    settings->setAttribute("projectname", mainModel.getProjectName());
    settings->setAttribute("trackwidth", mainModel.getWidth());
    project.addChildElement(settings);

    // save midi tracks
    juce::XmlElement* midiTrackElements = new juce::XmlElement("TRACKS");
    for (auto* midiTrack : mainModel.getMidiTracks())
    {
        juce::XmlElement* midiTrackElement = new juce::XmlElement("TRACK");
        convertMidiTrackData(*midiTrackElement, midiTrack);
        midiTrackElements->addChildElement(midiTrackElement);
    }
    project.addChildElement(midiTrackElements);

    //xmlDoc.append(project.createDocument(juce::String()), 200000);
    xmlDoc.append(project.toString(), 200000);
    return xmlDoc;
}

void FileSaver::convertMidiTrackData(juce::XmlElement& element, MidiTrack* midiTrack)
{
    // Store all attributes.
    element.setAttribute("name", midiTrack->getTrackName());
    element.setAttribute("colour", midiTrack->getColour().toString());
    element.setAttribute("audible", midiTrack->isAudible());
    element.setAttribute("visible", midiTrack->isVisible());

    //S tore all paths.
    juce::XmlElement* pathObjects = new juce::XmlElement("PATHS");
    for (auto* path : midiTrack->getPaths())
    {
        juce::XmlElement* pathToStore = new juce::XmlElement("Path");
        juce::String pathString = path->toString();
        pathToStore->setAttribute("data", pathString);
        pathObjects->addChildElement(pathToStore);
    }
    element.addChildElement(pathObjects);

    // Store midi data.
    juce::XmlElement* midiData = new juce::XmlElement("MIDIDATA");
    midiData->setAttribute("program", midiTrack->getProgram());
    midiData->setAttribute("channel", midiTrack->getChannel());
    element.addChildElement(midiData);

    juce::XmlElement* velocity = new juce::XmlElement("VELOCITY");
    
    // Iterate through the list of points except from the first and last one, because
    // they are going to be created automatically while creating a new instance.
    for (int i = 1; i < midiTrack->getMidiVelocityData().getPointVector().size() - 1; ++i)
    {
        juce::XmlElement* point = new juce::XmlElement("Point");
        point->setAttribute("x", midiTrack->getMidiVelocityData().getPointVector()[i]->getX());
        point->setAttribute("y", midiTrack->getMidiVelocityData().getPointVector()[i]->getY());
        velocity->addChildElement(point);
    }
    element.addChildElement(velocity);
}
