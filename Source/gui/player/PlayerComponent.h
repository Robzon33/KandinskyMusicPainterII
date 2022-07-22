/*
  ==============================================================================

    PlayerComponent.h
    Created: 11 Jul 2022 6:49:56pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../player/MidiPlayer.h"

class PlayerComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    PlayerComponent(MidiPlayer&);
    ~PlayerComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
private:
    MidiPlayer& player;
    juce::Colour colour;

    std::unique_ptr<juce::DrawableButton> playButton, pauseButton, stopButton;
    std::unique_ptr<juce::Slider> tempoSlider;

    void initSlider();
    void initButtons();
};
