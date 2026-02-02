#include "CrossFader.h"

void CrossFader::prepare(double sampleRate, float fadeTimeSeconds)
{
    currentBus = targetBus = requestedBus = 0;

    fader.reset(sampleRate, fadeTimeSeconds);
    fader.setCurrentAndTargetValue(0.0);
}

void CrossFader::requestBus(int newBus)
{
    requestedBus = newBus;
}

float CrossFader::getNextValue()
{
    return fader.getNextValue();
}

void CrossFader::updateBusesWhenPossible()
{
    if (!fader.isSmoothing()) // i.e. idle
    {
        if (targetBus != requestedBus)
        {
            currentBus = targetBus;
            fader.setCurrentAndTargetValue(0.0);
            targetBus = requestedBus;
        }

        if (currentBus != targetBus)
        {
            fader.setTargetValue(1.0);
        }
    }
}
