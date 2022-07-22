/*
  ==============================================================================

    MidiPlayer.h
    Created: 11 Jul 2022 3:54:35pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../model/MainModel.h"

class MidiPlayer :  private juce::HighResolutionTimer,
                    public juce::ChangeBroadcaster
{
public:
    MidiPlayer(MainModel& mm);
    ~MidiPlayer();

    void hiResTimerCallback() override;
    void play();
    void stop();
    void pause();
    juce::MidiBuffer getMidiBuffer();
    int getPosition();
    int getSpeed();
    void setSpeed(int pixelsPerSecond);

    juce::OwnedArray<juce::MidiMessage>& getMidiMessageList();
private:
    juce::MidiBuffer midiBuffer;
    MainModel& mainModel;
    int position; /* The players position in pixels (x-axis). */
    int speed; /* The players speed in pixel per second. */
    bool processorFlag; /* Indicates whether the processor is allowed to acces the midi buffer. */
    juce::OwnedArray<juce::Array<bool>> previousNotesOn; /* Indicates for each midi channel wether a certain note has been played in the previous step. */
    juce::OwnedArray<juce::MidiMessage> midiMessageList;

    /** Produces note off midi messages and adds them to the midi buffer. */
    void sendAllNotesOffForEachChannel();

    /** Resets or initializes the previous notes on array with false values for each channel. */
    void resetPreviousNotesOn();

    /** Produces Midi Messages and adds them to the Midi Buffer. */
    void produceMidiMessages();

    /** Adds an midi message to the players outgoing messages list. */
    void addMessageToList(const juce::MidiMessage& message);

    /** This is used to dispatch an outgoing message to the message thread. */
    struct OutgoingMessageCallback : public juce::CallbackMessage
    {
        OutgoingMessageCallback(MidiPlayer* mp, const juce::MidiMessage& m)
            : message (m), midiPlayer (mp)
        {
        }

        void messageCallback() override
        {
            if (midiPlayer != nullptr)
                midiPlayer->addMessageToList(message);
        }

        juce::MidiMessage message;
        juce::WeakReference<MidiPlayer> midiPlayer;
    };

    juce::WeakReference<MidiPlayer>::Master masterReference;
    friend class juce::WeakReference<MidiPlayer>;
};
