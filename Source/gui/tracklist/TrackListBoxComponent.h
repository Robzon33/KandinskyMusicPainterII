/*
  ==============================================================================

    TrackListBoxComponent.h
    Created: 11 Jul 2022 6:50:52pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../model/MainModel.h"
#include "../CommandIDs.h"
#include "TrackConfigComponent.h"

class TrackListBoxComponent :   public juce::ListBox,
                                private juce::ListBoxModel,
                                private juce::ChangeListener
{
public:
    TrackListBoxComponent(MainModel&, juce::ApplicationCommandManager&);
    ~TrackListBoxComponent();

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height,
        bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent& event) override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void showTrackConfigDialog(int row);
private:
    MainModel& mainModel;
    juce::ApplicationCommandManager& commandManager;
};
