/*
  ==============================================================================

    ToolBarComponent.cpp
    Created: 11 Jul 2022 6:50:19pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "ToolBarComponent.h"

ToolBarComponent::ToolBarComponent(juce::ApplicationCommandManager& acm)
    : commandManager (acm)
{
    for (int i = 0; i < Kmp2Tool::getNumberOfTools(); ++i)
    {
        auto* newButton = Kmp2Tool::getButton(i);
        newButton->addListener(this);
        newButton->setRadioGroupId(12345);
        buttons.add(newButton);
        addAndMakeVisible(newButton);

        if (i == 0)
        {
            newButton->setToggleState(true, juce::dontSendNotification);
        }
    }
}

ToolBarComponent::~ToolBarComponent()
{
}

void ToolBarComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.brighter(0.2f));
}

void ToolBarComponent::resized()
{
    auto b = getLocalBounds();

    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i]->setBounds(b.removeFromLeft(60));
    }
}

void ToolBarComponent::buttonClicked(juce::Button* button)
{
    commandManager.invokeDirectly(CommandIDs::selectTool, true);
}

int ToolBarComponent::getIndexOfSelectedButton()
{
    for (int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i]->getToggleState())
        {
            return i;
        }
    }
    return -1;
}
