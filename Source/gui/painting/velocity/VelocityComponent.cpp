/*
  ==============================================================================

    VelocityComponent.cpp
    Created: 12 Jul 2022 4:39:47pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(MidiTrack& mt)
    : midiTrack (mt)
{
}

VelocityComponent::~VelocityComponent()
{
}

void VelocityComponent::mouseDown(const juce::MouseEvent& event)
{
    if (event.mods.isLeftButtonDown())
    {
        int index = midiTrack.getMidiVelocityData()
                             .getIndexOfPoint((int)event.getMouseDownX(),
                                              (int)event.getMouseDownY());
        
        if (index == -1)
        {
            midiTrack.getMidiVelocityData().addPoint((int)event.getMouseDownX(),
                                                     (int)event.getMouseDownY());
        }
        else
        {
            midiTrack.getMidiVelocityData().deletePoint(index);
        }
    }
    repaint();
}

void VelocityComponent::paint (juce::Graphics& g)
{
    g.setColour(midiTrack.getColour());
    
    int prevX = -1, prevY = -1;
    
    for (auto* point : midiTrack.getMidiVelocityData().getPointVector())
    {
        if (prevX >= 0 && prevY >= 0)
        {
            g.drawLine(prevX, prevY, point->getX(), point->getY(), 1);
        }
        g.fillRoundedRectangle(point->getX() - 2, point->getY() - 2, 4, 4, 1.5f);
        prevX = point->getX();
        prevY = point->getY();
    }
}
