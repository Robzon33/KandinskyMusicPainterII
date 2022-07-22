/*
  ==============================================================================

    PropertyComponents.h
    Created: 12 Jul 2022 11:08:09am
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class ColourButtonPropertyComponent : public juce::ButtonPropertyComponent,
    public juce::ChangeListener,
    public juce::ChangeBroadcaster
{
public:
    ColourButtonPropertyComponent(const juce::String& propertyName, juce::Colour currentColour)
        : ButtonPropertyComponent(propertyName, true)
    {
        colour = currentColour;
    };

    void buttonClicked() override
    {
        std::unique_ptr<juce::ColourSelector> colourSelector;
        colourSelector.reset(new juce::ColourSelector());
        colourSelector.get()->setName("background");
        colourSelector.get()->setCurrentColour(colour);
        colourSelector.get()->addChangeListener(this);
        colourSelector.get()->setColour(juce::ColourSelector::backgroundColourId, juce::Colours::transparentBlack);
        colourSelector.get()->setSize(300, 400);

        juce::CallOutBox::launchAsynchronously(std::move(colourSelector), getScreenBounds(), nullptr);

        refresh();
    };

    juce::String getButtonText() const override
    {
        return "Select Colour";
    };

    void changeListenerCallback(ChangeBroadcaster* source) override
    {
        if (juce::ColourSelector* cs = dynamic_cast<juce::ColourSelector*> (source))
        {
            colour = cs->getCurrentColour();
            sendChangeMessage();
        }
    };

    juce::Colour getNewColour()
    {
        return colour;
    };
private:
    juce::Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColourButtonPropertyComponent)
};

//==============================================================================
class SelectBooleanComponent : public juce::BooleanPropertyComponent,
    public juce::ChangeBroadcaster
{
public:
    SelectBooleanComponent(const juce::String& propertyName, bool currentlySelected)
        : BooleanPropertyComponent(propertyName, "", "")
    {
        isSelected = currentlySelected;
    };

    void setState(bool newState)
    {
        isSelected = newState;
        refresh();
        sendChangeMessage();
    };

    bool getState() const
    {
        return isSelected;
    };
private:
    bool isSelected;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SelectBooleanComponent)
};

//==============================================================================
class SelectProgramComponent : public juce::ChoicePropertyComponent,
    public juce::ChangeBroadcaster
{
public:
    SelectProgramComponent(const juce::String& propertyName, int program)
        : ChoicePropertyComponent(propertyName)
    {
        selectedProgram = program;

        for (int i = 0; i < 128; ++i)
        {
            juce::String gmInstrumentName;
            gmInstrumentName << static_cast<int> (i);
            gmInstrumentName << juce::String(" ");
            gmInstrumentName << juce::MidiMessage::getGMInstrumentName(i);
            choices.add(gmInstrumentName);
        }
    };

    void setIndex(int newIndex) override
    {
        selectedProgram = newIndex;
        refresh();
        sendChangeMessage();
    };

    int getIndex() const override
    {
        return selectedProgram;
    };
private:
    int selectedProgram;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SelectProgramComponent)
};

//==============================================================================
class SelectChannelComponent : public juce::ChoicePropertyComponent,
    public juce::ChangeBroadcaster
{
public:
    SelectChannelComponent(const juce::String& propertyName, int currentChannel)
        : ChoicePropertyComponent(propertyName)
    {
        index = currentChannel - 1;

        for (int i = 1; i < 17; ++i)
        {
            juce::String channelString;
            channelString << juce::String("Channel ");
            channelString << static_cast<int> (i);
            if (i == 10)
                channelString << juce::String(" GM Percussion");
            choices.add(channelString);
        }
    };

    void setIndex(int newIndex) override
    {
        index = newIndex;
        sendChangeMessage();
    };

    int getIndex() const override
    {
        return index;
    };

    int getChannel()
    {
        return index + 1;
    };
private:
    int index;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SelectChannelComponent)
};
