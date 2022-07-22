/*
  ==============================================================================

    MainComponent.h
    Created: 11 Jul 2022 6:47:21pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include "../model/MainModel.h"
#include "../player/MidiPlayer.h"

#include "menu/MenuBarComponent.h"
#include "player/PlayerComponent.h"
#include "tracklist/TrackListBoxComponent.h"
#include "toolbar/ToolBarComponent.h"
#include "painting/MainPaintingComponent.h"
#include "midiMonitor/MidiMonitorComponent.h"
#include "extensions/FileSaver.h"
#include "extensions/FileLoader.h"

class MainComponent : public juce::Component,
                      public juce::ApplicationCommandTarget
{
public:
    MainComponent(MainModel&, MidiPlayer&);
    ~MainComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    juce::ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& c) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo& info) override;
private:
    MainModel& model;
    MidiPlayer& player;
    bool showMidiMonitor;
    juce::ApplicationCommandManager commandManager;
    std::unique_ptr<juce::FileChooser> fileChooser;

    /* Child components */
    std::unique_ptr<MenuBarComponent> menuBar;
    std::unique_ptr<PlayerComponent> playerBar;
    std::unique_ptr<TrackListBoxComponent> trackList;
    std::unique_ptr<ToolBarComponent> toolBar;
    std::unique_ptr<MainPaintingComponent> mainPaintingArea;
    std::unique_ptr<juce::Viewport> mainPaintingAreaViewport;
    std::unique_ptr<MidiMonitorComponent> midiMonitor;
};
