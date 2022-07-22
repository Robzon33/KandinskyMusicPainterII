/*
  ==============================================================================

    MidiPlayer.cpp
    Created: 11 Jul 2022 3:54:35pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "MidiPlayer.h"

MidiPlayer::MidiPlayer(MainModel& mm)
    : mainModel (mm)
{
    this->processorFlag = false;
    this->position = 0;
    this->speed = 50;
    this->resetPreviousNotesOn();
}

MidiPlayer::~MidiPlayer()
{
    this->stop();
    this->masterReference.clear();
}

void MidiPlayer::hiResTimerCallback()
{
    this->position = position + 1;
    if (position >= mainModel.getWidth())
    {
        position = 0;
    }
    
    processorFlag = true;
    sendChangeMessage();
}

void MidiPlayer::play()
{
    startTimer(1000 / this->speed);
}

void MidiPlayer::stop()
{
    stopTimer();
    this->sendAllNotesOffForEachChannel();
    midiMessageList.clear(true);
    this->position = 0;
    this->resetPreviousNotesOn();
}

void MidiPlayer::pause()
{
    stopTimer();
    midiBuffer.addEvent(juce::MidiMessage::allNotesOff(1), 1);
    this->resetPreviousNotesOn();
}

juce::MidiBuffer MidiPlayer::getMidiBuffer()
{
    juce::MidiBuffer bufferToReturn;
    
    if (processorFlag)
    {
        this->produceMidiMessages();
        bufferToReturn = this->midiBuffer;
        this->midiBuffer.clear();
        processorFlag = false;
    }
    return bufferToReturn;
}

int MidiPlayer::getPosition()
{
    return this->position;
}

int MidiPlayer::getSpeed()
{
    return this->speed;
}

void MidiPlayer::setSpeed(int pixelsPerSecond)
{
    this->speed = pixelsPerSecond;
    
    if (isTimerRunning())
    {
        this->play();
    }
}

juce::OwnedArray<juce::MidiMessage>& MidiPlayer::getMidiMessageList()
{
    return this->midiMessageList;
}

void MidiPlayer::sendAllNotesOffForEachChannel()
{
    for (int i = 1; i <= 16; ++i)
    {
        juce::MidiMessage message(juce::MidiMessage::allNotesOff(i));
        if (message.getRawDataSize() == 3)
        {
            midiBuffer.addEvent(message, 0);
            this->processorFlag = true;
        }
    }
}

void MidiPlayer::resetPreviousNotesOn()
{
    previousNotesOn.clear(true);
    for (int i = 1; i <= 16; i++)
    {
        juce::Array<bool>* newArray = new juce::Array<bool>;
        for (int j = 0; j < 128; j++)
        {
            newArray->add(false);
        }
        previousNotesOn.add(newArray);
    }
}

void MidiPlayer::produceMidiMessages()
{
    juce::Array<float> yValues;

    for (auto* track : mainModel.getMidiTracks())
    {
        int channel = track->getChannel();

        // initialize a new array on stack to store new note on messages
        juce::Array<bool> noteOnMessages;
        for (int j = 0; j < 128; ++j)
            noteOnMessages.add(false);

        // calculate intersections
        yValues = track->calculateIntersections(this->position);

        // produce note on messages
        if (!yValues.isEmpty())
        {
            for (int i = 0; i < yValues.size(); i++)
            {
                int note = static_cast<int>(127 - yValues[i]);
                
                if (note >= 0 && note <= 127)
                {
                    if (!(previousNotesOn.getUnchecked(channel)->getUnchecked(note)))
                    {
                        juce::uint8 velocity = track->getMidiVelocityData().getVelocity(this->position);
                        juce::MidiMessage message(juce::MidiMessage::noteOn(channel, note, velocity));
                        message.setTimeStamp(this->position);
                        this->midiBuffer.addEvent(message, 0);

                        (new OutgoingMessageCallback(this, message))->post();
                    }
                    noteOnMessages.set(note, true);
                }
            }
        }

        // produce note off messages
        for (int k = 0; k < 128; ++k)
        {
            if (previousNotesOn.getUnchecked(channel)->getUnchecked(k) &&
                !noteOnMessages.getUnchecked(k))
            {
                juce::MidiMessage message(juce::MidiMessage::noteOff(channel, k));
                message.setTimeStamp(this->position);
                (new OutgoingMessageCallback(this, message))->post();
                this->midiBuffer.addEvent(message, 0);
            }
        }

        previousNotesOn.getUnchecked(channel)->swapWith(noteOnMessages);
    }
}

void MidiPlayer::addMessageToList(const juce::MidiMessage& message)
{
    midiMessageList.add(new juce::MidiMessage(message));

    if (midiMessageList.size() > 200)
    {
        midiMessageList.removeRange(0, 1, true);
    }
    
    sendChangeMessage();
}
