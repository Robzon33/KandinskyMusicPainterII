/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/MainComponent.h"

//==============================================================================
/**
*/
class KandinskyMusicPainterIIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KandinskyMusicPainterIIAudioProcessorEditor (KandinskyMusicPainterIIAudioProcessor&,
                                                 MainModel& m,
                                                 MidiPlayer& mp);
    ~KandinskyMusicPainterIIAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KandinskyMusicPainterIIAudioProcessor& audioProcessor;
    
    // These references are provided as a quick way for your editor
    // to access the model and player.
    MainModel& mainModel;
    MidiPlayer& midiPlayer;
    
    // Child component.
    std::unique_ptr<MainComponent> mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KandinskyMusicPainterIIAudioProcessorEditor)
};
