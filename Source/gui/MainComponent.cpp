/*
  ==============================================================================

    MainComponent.cpp
    Created: 11 Jul 2022 6:47:21pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent(MainModel& m, MidiPlayer& mp)
    : model (m), player (mp)
{
    menuBar.reset(new MenuBarComponent(model, commandManager));
    addAndMakeVisible(menuBar.get());
    
    playerBar.reset(new PlayerComponent(player));
    addAndMakeVisible(playerBar.get());
    
    trackList.reset(new TrackListBoxComponent(model, commandManager));
    addAndMakeVisible(trackList.get());

    toolBar.reset(new ToolBarComponent(commandManager));
    addAndMakeVisible(toolBar.get());
    
    mainPaintingArea.reset(new MainPaintingComponent(model, player, commandManager));
    addAndMakeVisible(mainPaintingArea.get());
    
    mainPaintingAreaViewport.reset(new juce::Viewport("Main Painting Area Viewport"));
    addAndMakeVisible(mainPaintingAreaViewport.get());
    mainPaintingAreaViewport->setViewedComponent(mainPaintingArea.get(), false);
    
    midiMonitor.reset (new MidiMonitorComponent(player));
    addAndMakeVisible(midiMonitor.get());

    commandManager.registerAllCommandsForTarget(this);
    commandManager.setFirstCommandTarget(this);

    showMidiMonitor = false;
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(juce::Graphics& g)
{
}

void MainComponent::resized()
{
    auto b = getLocalBounds();

    menuBar->setBounds (b.removeFromTop(30));
    playerBar->setBounds (b.removeFromBottom(100));
    trackList->setBounds (b.removeFromLeft(150));
    if (showMidiMonitor)
    {
        midiMonitor->setBounds (b.removeFromRight(400));
    }
    toolBar->setBounds (b.removeFromTop(60));
    mainPaintingAreaViewport->setBounds (b);
}

juce::ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
    // ich glaube hier muss was hin, wenn es ein weiteres target gibt
    return nullptr;
}

void MainComponent::getAllCommands(juce::Array<juce::CommandID>& c)
{
    juce::Array<juce::CommandID> commands{ CommandIDs::addMidiTrack,
                                           CommandIDs::deleteTrack,
                                           CommandIDs::deleteAllTracks,
                                           CommandIDs::newProject,
                                           CommandIDs::saveProject,
                                           CommandIDs::loadProject,
                                           CommandIDs::openProjectConfig,
                                           CommandIDs::selectTrack,
                                           CommandIDs::selectTool,
                                           CommandIDs::showMidiMonitor};

    c.addArray(commands);
}

void MainComponent::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{
    switch (commandID)
    {
    case CommandIDs::addMidiTrack:
        result.setInfo("Add", "Adds a new track to the current project", "Track", 0);
        break;
    case CommandIDs::deleteTrack:
        result.setInfo("Delete", "Deletes the currently selected track", "Track", 0);
        break;
    case CommandIDs::deleteAllTracks:
        result.setInfo("Delete all", "Deletes all tracks from the current project", "Track", 0);
        break;
    case CommandIDs::newProject:
        result.setInfo("New project", "Closes the current project and creates a new one", "Project", 0);
        break;
    case CommandIDs::saveProject:
        result.setInfo("Save project", "Saves the current project", "Project", 0);
        break;
    case CommandIDs::loadProject:
        result.setInfo("Load project", "Loads a selected file", "Project", 0);
        break;
    case CommandIDs::openProjectConfig:
        result.setInfo("Configuration", "Opens a menu to configure the current project", "Project", 0);
        break;
    case CommandIDs::selectTrack:
        result.setInfo("Select Track", "Selects a track from the tracklist", "Track", 0);
        break;
    case CommandIDs::selectTool:
        result.setInfo("Select Tool", "Selects a tool to paint", "Drawing", 0);
        break;
    case CommandIDs::showMidiMonitor:
        result.setInfo("Midi monitor", "Enables/Disables the midi monitor", "View", 0);
        result.setTicked(showMidiMonitor);
        break;
    default:
        break;
    }
}

bool MainComponent::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
    case CommandIDs::addMidiTrack:
    {
        if (model.addMidiTrack())
        {
            int index = model.getIndexOfLastTrack();
            MidiTrack* newTrack = model.getMidiTrack(index);
            mainPaintingArea->addTrackComponents(newTrack);
            trackList->updateContent();
            trackList->selectRow(index);
        }
        break;
    }
    case CommandIDs::deleteTrack:
    {
        int index = trackList->getSelectedRow();
        model.deleteTrack (index);
        mainPaintingArea->deleteTrackComponent (index);
        trackList->updateContent();
        if (trackList->getSelectedRow() == -1)
        {
            trackList->selectRow (model.getIndexOfLastTrack());
        }
        break;
    }
    case CommandIDs::deleteAllTracks:
    {
        mainPaintingArea->deleteAllTrackComponents();
        model.deleteAllTracks();        
        trackList->updateContent();
        break;
    }
    case CommandIDs::newProject:
    {
        mainPaintingArea->deleteAllTrackComponents();
        model.reset();
        trackList->updateContent();
        break;
    }
    case CommandIDs::saveProject:
    {
        fileChooser = std::make_unique<juce::FileChooser>("Save project",
                                                          juce::File(),
                                                          "*.kmp");
        auto folderChooserFlags = juce::FileBrowserComponent::saveMode
                                | juce::FileBrowserComponent::canSelectFiles;
        
        fileChooser->launchAsync(folderChooserFlags, [this] (const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            
            if (file != juce::File{})
            {
                juce::String stringToAppend = FileSaver::convertProjectToXML(model);
                file.replaceWithText(stringToAppend);
            }
        });
        break;
    }
    case CommandIDs::loadProject:
    {
        fileChooser = std::make_unique<juce::FileChooser>("Load project",
                                                          juce::File(),
                                                          "*.kmp");
        
        auto folderChooserFlags = juce::FileBrowserComponent::openMode
                                | juce::FileBrowserComponent::canSelectFiles;
        
        fileChooser->launchAsync(folderChooserFlags, [this] (const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            
            if (file != juce::File{})
            {
                FileLoader::loadFile(juce::parseXML(file), model);
                trackList->updateContent();
                mainPaintingArea->loadModel();
            }
        });
        break;
    }
//    case CommandIDs::openProjectConfig:
//    {
//        configDialog.reset(new ConfigDialog(settings));
//        addAndMakeVisible(configDialog.get());
//        juce::DialogWindow* dialogWindow = configDialog->getDialogWindow();
//        if (dialogWindow != nullptr)
//        {
//            dialogWindow->centreWithSize(300, 300);
//        }
//        break;
//    }
    case CommandIDs::selectTrack:
    {
        auto index = trackList->getSelectedRow();
        mainPaintingArea->setSelectedTrack (index);
        break;
    }
    case CommandIDs::selectTool:
    {
        auto index = toolBar.get()->getIndexOfSelectedButton();
        mainPaintingArea->setSelectedTool (index);
        break;
    }
    case CommandIDs::showMidiMonitor:
    {
        if (showMidiMonitor) { showMidiMonitor = false; }
        else                 { showMidiMonitor = true; }
        midiMonitor->setVisible(showMidiMonitor);
        resized();
        break;
    }
    default:
        return false;
    }

    return true;
}
