/*
  ==============================================================================

    MenuBarComponent.cpp
    Created: 11 Jul 2022 6:49:41pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "MenuBarComponent.h"

MenuBarComponent::MenuBarComponent(MainModel& mm, juce::ApplicationCommandManager& acm)
    : mainModel(mm), commandManager (acm)
{
    menuBar.reset(new juce::MenuBarComponent(this));
    addAndMakeVisible(menuBar.get());
    setApplicationCommandManagerToWatch(&commandManager);
}

MenuBarComponent::~MenuBarComponent()
{
}

void MenuBarComponent::resized()
{
    menuBar->setBounds(getLocalBounds());
}

juce::StringArray MenuBarComponent::getMenuBarNames()
{
    return { "Project", "View"};
}

juce::PopupMenu MenuBarComponent::getMenuForIndex(int menuIndex, const juce::String&)
{
    juce::PopupMenu menu;

    if (menuIndex == 0)
    {
        menu.addCommandItem(&commandManager, CommandIDs::newProject);
        menu.addCommandItem(&commandManager, CommandIDs::saveProject);
        menu.addCommandItem(&commandManager, CommandIDs::loadProject);
        menu.addSeparator();
        menu.addCommandItem(&commandManager, CommandIDs::addMidiTrack);
        menu.addCommandItem(&commandManager, CommandIDs::deleteTrack);
        menu.addCommandItem(&commandManager, CommandIDs::deleteAllTracks);
        menu.addSeparator();
        menu.addCommandItem(&commandManager, CommandIDs::openProjectConfig);
    }
    if (menuIndex == 1)
    {
        menu.addCommandItem(&commandManager, CommandIDs::setZoom100);
        menu.addCommandItem(&commandManager, CommandIDs::setZoom200);
        menu.addCommandItem(&commandManager, CommandIDs::setZoom400);
        menu.addSeparator();
        menu.addCommandItem(&commandManager, CommandIDs::showMidiMonitor);
    }

    return menu;
}

void MenuBarComponent::menuItemSelected(int menuItemId, int)
{
}
