/*
  ==============================================================================

    Drawer.cpp
    Created: 12 Jul 2022 9:55:20pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "Drawer.h"

Drawer::Drawer()
{
    kmp2tool.reset(Kmp2Tool::Create(static_cast<Kmp2ToolIDs>(0)));
}

Drawer::~Drawer()
{
}

void Drawer::setSelectedTool(int index)
{
    kmp2tool.reset(Kmp2Tool::Create(static_cast<Kmp2ToolIDs>(index)));
}

void Drawer::draw(float x, float y, juce::Path* path)
{
    if (startPoint == juce::Point<float>())
    {
        startPoint = juce::Point<float>(x, y);
    }
    else
    {
        kmp2tool.get()->perform(startPoint, juce::Point<float> (x, y), path);
    }
}

void Drawer::reset()
{
    startPoint = juce::Point<float>();
}
