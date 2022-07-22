/*
  ==============================================================================

    PlayerComponent.cpp
    Created: 11 Jul 2022 6:49:56pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(MidiPlayer& mp)
    : player(mp)
{
    colour = juce::Colours::pink;
    initSlider();
    initButtons();
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::paint(juce::Graphics& g)
{
    g.fillAll(colour.withAlpha(0.4f));
}

void PlayerComponent::resized()
{
    auto b = getLocalBounds();

    tempoSlider->setBounds(b.removeFromLeft(getWidth() / 4).reduced(10));
    stopButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(30));
    playButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(10));
    pauseButton->setBounds(b.removeFromLeft(getWidth() / 4).reduced(30));
}

void PlayerComponent::buttonClicked(juce::Button* button)
{
    if (button == playButton.get())     { player.play(); }
    if (button == pauseButton.get())    { player.pause(); }
    if (button == stopButton.get())     { player.stop(); }
}

void PlayerComponent::sliderValueChanged(juce::Slider* slider)
{
    player.setSpeed((int)slider->getValue());
}

void PlayerComponent::initSlider()
{
    tempoSlider.reset(new juce::Slider());
    addAndMakeVisible(tempoSlider.get());
    tempoSlider->setRange(10, 100, 1);
    tempoSlider->setValue(player.getSpeed());
    tempoSlider->setSliderStyle(juce::Slider::Rotary);
    tempoSlider->setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, false);
    tempoSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 120, 30);
    tempoSlider->setTextValueSuffix(" pixels per second");
    tempoSlider->addListener(this);
}

void PlayerComponent::initButtons()
{
    juce::DrawableImage playImage;
    playImage.setImage(juce::ImageCache::getFromMemory(BinaryData::playerplay_png,
        BinaryData::playerplay_pngSize));
    juce::DrawableImage playImageOver(playImage);
    playImageOver.setOverlayColour(juce::Colours::black.withAlpha(0.3f));

    juce::DrawableImage playImageDown(playImage);
    playImageDown.setOverlayColour(juce::Colours::black.withAlpha(0.7f));

    //==============================================================================
    juce::DrawableImage pauseImage;
    pauseImage.setImage(juce::ImageCache::getFromMemory(BinaryData::playerpause_png,
        BinaryData::playerpause_pngSize));
    juce::DrawableImage pauseImageOver(pauseImage);
    pauseImageOver.setOverlayColour(juce::Colours::black.withAlpha(0.3f));

    juce::DrawableImage pauseImageDown(pauseImage);
    pauseImageDown.setOverlayColour(juce::Colours::black.withAlpha(0.7f));

    //==============================================================================
    juce::DrawableImage stopImage;
    stopImage.setImage(juce::ImageCache::getFromMemory(BinaryData::playerstop_png,
        BinaryData::playerstop_pngSize));
    juce::DrawableImage stopImageOver(stopImage);
    stopImageOver.setOverlayColour(juce::Colours::black.withAlpha(0.3f));

    juce::DrawableImage stopImageDown(stopImage);
    stopImageDown.setOverlayColour(juce::Colours::black.withAlpha(0.7f));

    //==============================================================================
    playButton.reset(new juce::DrawableButton("play", juce::DrawableButton::ImageFitted));
    playButton->setImages(&playImage, &playImageOver, &playImageDown);
    this->addAndMakeVisible(playButton.get());
    playButton->addListener(this);

    pauseButton.reset(new juce::DrawableButton("pause", juce::DrawableButton::ImageFitted));
    pauseButton->setImages(&pauseImage, &pauseImageOver, &pauseImageDown);
    this->addAndMakeVisible(pauseButton.get());
    pauseButton->addListener(this);

    stopButton.reset(new juce::DrawableButton("stop", juce::DrawableButton::ImageFitted));
    stopButton->setImages(&stopImage, &stopImageOver, &stopImageDown);
    this->addAndMakeVisible(stopButton.get());
    stopButton->addListener(this);
}
