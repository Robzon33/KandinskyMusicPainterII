/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KandinskyMusicPainterIIAudioProcessorEditor::KandinskyMusicPainterIIAudioProcessorEditor (KandinskyMusicPainterIIAudioProcessor& p, MainModel& m, MidiPlayer& mp)
    : AudioProcessorEditor (&p), audioProcessor (p), mainModel(m), midiPlayer(mp)
{
    mainComponent.reset(new MainComponent(mainModel, midiPlayer));
    addAndMakeVisible(mainComponent.get());
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 800);
}

KandinskyMusicPainterIIAudioProcessorEditor::~KandinskyMusicPainterIIAudioProcessorEditor()
{
}

//==============================================================================
void KandinskyMusicPainterIIAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void KandinskyMusicPainterIIAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    juce::Rectangle<int> area(getLocalBounds());

    if (mainComponent != nullptr)
    {
        mainComponent->setBounds(area);
    }
}
