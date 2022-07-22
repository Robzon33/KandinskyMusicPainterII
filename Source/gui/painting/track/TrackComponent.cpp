/*
  ==============================================================================

    TrackComponent.cpp
    Created: 12 Jul 2022 4:39:26pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "TrackComponent.h"

TrackComponent::TrackComponent(MidiTrack& mt, Drawer& d)
    : track(mt), drawer(d)
{
}

TrackComponent::~TrackComponent()
{}

void TrackComponent::paint(juce::Graphics& g)
{
    if (track.isVisible())
    {
        g.setColour(track.getColour());

        //paint existing paths
        juce::OwnedArray<juce::Path>& paths = track.getPaths();
        for (auto* path : paths)
        {
            auto pathToDraw = *path;
            pathToDraw.applyTransform(juce::AffineTransform::scale(1));
            g.strokePath(pathToDraw, juce::PathStrokeType(1));
        }

        // creating a preview while drawing
        if (!cp.isEmpty())
        {
            g.setColour(track.getColour().brighter(0.5f));
            //cp.applyTransform(juce::AffineTransform::scale(1.0f));
            g.strokePath(cp, juce::PathStrokeType(1));
        }
        
    }
}

void TrackComponent::mouseDrag(const juce::MouseEvent& event)
{
    drawer.draw((int)event.position.getX(), (int)event.position.getY(), &cp);
    repaint();
}

void TrackComponent::mouseUp(const juce::MouseEvent& event)
{
    drawer.draw((int)event.position.getX(), (int)event.position.getY(), &cp);
    track.addPath(cp);
    cp.clear();
    drawer.reset();
    repaint();
}
