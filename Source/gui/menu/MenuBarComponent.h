/*
  ==============================================================================

    MenuBarComponent.h
    Created: 11 Jul 2022 6:49:41pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../model/MainModel.h"
#include "../CommandIDs.h"

class MenuBarComponent :    public juce::Component,
                            public juce::MenuBarModel
{
public:
    MenuBarComponent(MainModel&, juce::ApplicationCommandManager&);
    ~MenuBarComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int menuIndex, const juce::String& /*menuName*/) override;
    void menuItemSelected(int menuItemId, int /*topLevelMenuIndex*/) override;
private:
    std::unique_ptr<juce::MenuBarComponent> menuBar;
    MainModel& mainModel;
    juce::ApplicationCommandManager& commandManager;
};
