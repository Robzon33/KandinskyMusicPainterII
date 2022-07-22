/*
  ==============================================================================

    MainModel.cpp
    Created: 11 Jul 2022 3:53:20pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "MainModel.h"

MainModel::MainModel()
{
    this->projectName = "unnamed";
    this->width = 800;
}

MainModel::~MainModel()
{
}

void MainModel::setProjectName(juce::String newProjectName)
{
    this->projectName = newProjectName;
}

juce::String MainModel::getProjectName()
{
    return this->projectName;
}

void MainModel::setWidth(int newWidth)
{
    this->width = newWidth;
    
    for (auto* track : midiTracks)
    {
        track->setWidth(newWidth);
    }
}

int MainModel::getWidth()
{
    return this->width;
}

int MainModel::getMaxNumberOfMidiTracks()
{
    return this->maxNumberOfMidiTracks;
}

bool MainModel::addMidiTrack()
{
    if (midiTracks.size() < this->maxNumberOfMidiTracks - 1)
    {
        MidiTrack* newTrack = new MidiTrack(this->width);
        midiTracks.add(newTrack);
        return true;
    }

    return false;
}

MidiTrack* MainModel::getMidiTrack(int index)
{
    return midiTracks[index];
}

void MainModel::deleteTrack(int index)
{
    midiTracks.remove(index);
}

void MainModel::deleteAllTracks()
{
    midiTracks.clear(true);
}

int MainModel::getIndexOfLastTrack()
{
    return midiTracks.size() - 1;
}

juce::String MainModel::getTrackName(int index)
{
    return midiTracks[index]->getTrackName();
}

juce::Array<MidiTrack*> MainModel::getAllTracks()
{
    juce::Array<MidiTrack*> tracksToReturn;

    for (auto* track : midiTracks)
    {
        tracksToReturn.add(track);
    }

    return tracksToReturn;
}

juce::OwnedArray<MidiTrack>& MainModel::getMidiTracks()
{
    return midiTracks;
}

int MainModel::getNumberOfTracks()
{
    return midiTracks.size();
}

void MainModel::updateTrackWidth(int newWidth)
{
    for (auto* track : midiTracks)
    {
        track->setWidth(newWidth);
    }
}

void MainModel::reset()
{
    this->deleteAllTracks();
    this->projectName = "unnamed";
    this->width = 800;
}
