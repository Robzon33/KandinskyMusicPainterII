/*
  ==============================================================================

    MidiVelocityData.cpp
    Created: 20 Jul 2022 12:15:37pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include "MidiVelocityData.h"

MidiVelocityData::MidiVelocityData(int width)
{
    this->width = width;
    this->pointVector.insert(0, new juce::Point<int>(0, this->defaultVelocityValue));
    this->pointVector.insert(1, new juce::Point<int>(this->width, this->defaultVelocityValue));
}

MidiVelocityData::~MidiVelocityData()
{
}

void MidiVelocityData::addPoint(int x, int y)
{
    if (this->pointVector.size() < this->maxNumberOfPoints)
    {
        for (int i = 0; i < this->pointVector.size(); ++i)
        {
            if (this->pointVector[i]->getX() > x)
            {
                this->pointVector.insert(i, new juce::Point<int>(x, y));
                break;
            }
        }
    }
}

void MidiVelocityData::deletePoint(int index)
{
    if (index > 0 && index < this->pointVector.size() - 1)
    {
        pointVector.remove(index);
    }
}

void MidiVelocityData::updateWidth(int newWidth)
{
    if (this->width > newWidth)
    {
        for (int i = pointVector.size() - 1; i >= 0; --i)
        {
            if (pointVector[i]->getX() > newWidth)
            {
                pointVector.remove(i, true);
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        pointVector.removeLast();
    }

    this->pointVector.add(new juce::Point<int>(newWidth, this->defaultVelocityValue));
    this->width = newWidth;
}

juce::OwnedArray<juce::Point<int>>& MidiVelocityData::getPointVector()
{
    return pointVector;
}

int MidiVelocityData::getIndexOfPoint(int x, int y)
{
    for (int i = 0; i < this->pointVector.size(); i++)
    {
        if (abs(this->pointVector[i]->getX() - x) < 4 &&
            abs(this->pointVector[i]->getY() - y) < 4)
        {
            return i;
        }
    }
    return -1;
}

int MidiVelocityData::getVelocity(int x)
{
    for (int i = 1; i < pointVector.size(); ++i)
    {
        if (x < pointVector[i]->getX())
        {
            float diffY = (float)pointVector[i]->getY() - (float)pointVector[i - 1]->getY();
            float diffX = (float)pointVector[i]->getX() - (float)pointVector[i - 1]->getX();
            float m = diffY / diffX;
            float n = pointVector[i]->getY() - (m * pointVector[i]->getX());
            return (int)(127 - ((m * x) + n));
        }
        if (x == pointVector[i]->getX())
            return (127 - pointVector[i]->getY());
    }
    return -1;
}
