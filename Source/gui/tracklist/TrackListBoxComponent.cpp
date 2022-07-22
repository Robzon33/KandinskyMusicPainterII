/*
  ==============================================================================

    TrackListBoxComponent.cpp
    Created: 11 Jul 2022 6:50:52pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "TrackListBoxComponent.h"

TrackListBoxComponent::TrackListBoxComponent(MainModel& mm, juce::ApplicationCommandManager& acm)
    : ListBox("Track List Box", nullptr), mainModel(mm), commandManager (acm)
{
    setOutlineThickness(0);
    setMultipleSelectionEnabled(false);
    setClickingTogglesRowSelection(true);
    setColour(backgroundColourId, juce::Colours::darkgrey.darker());
    setRowHeight(40);
    setModel(this);
}

TrackListBoxComponent::~TrackListBoxComponent()
{
    this->setModel(nullptr);
}

int TrackListBoxComponent::getNumRows()
{
    return mainModel.getNumberOfTracks();
}

void TrackListBoxComponent::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colour(128, 116, 105));
    else if (rowNumber % 2)
        g.fillAll(juce::Colours::darkgrey.darker(0.2f));

    g.setColour(mainModel.getMidiTrack(rowNumber)->getColour());
    g.setFont(height * 0.7f);

    g.drawText(mainModel.getTrackName(rowNumber), 5, 0, width, height,
        juce::Justification::centredLeft, true);
}

void TrackListBoxComponent::listBoxItemClicked(int row, const juce::MouseEvent& event)
{
    if (event.mods.isLeftButtonDown())
    {
        commandManager.invokeDirectly(CommandIDs::selectTrack, true);
    }
    if (event.mods.isRightButtonDown())
    {
        juce::PopupMenu m;
        m.addItem(100, "Edit");
        m.addSeparator();
        m.addItem(105, "Delete track");

        m.showMenuAsync (juce::PopupMenu::Options(),
                        [this, row] (int result)
                        {
                            if (result == 100)
                            {
                                showTrackConfigDialog(row);
                            }
                            else if (result == 105)
                            {
                                commandManager.invokeDirectly(CommandIDs::deleteTrack, true);
                            }
        });
    }
}

void TrackListBoxComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    this->repaint();
}

void TrackListBoxComponent::showTrackConfigDialog(int row)
{
    auto content = std::make_unique<TrackConfigComponent>(*mainModel.getMidiTrack(row));
    content->addChangeListener(this);
    content->setSize(300, 400);

    juce::CallOutBox::launchAsynchronously(std::move(content),
                                           getScreenBounds(),
                                           nullptr);
}
