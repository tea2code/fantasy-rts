#include "Frame.h"

#include <stdexcept>

frts::Frame::Frame(double deltaTime, unsigned long long number, double runTime)
    : deltaTime{deltaTime}, number{number}, runTime{runTime}
{
}

double frts::Frame::getDeltaTime() const
{
    return deltaTime;
}

unsigned long long frts::Frame::getNumber() const
{
    return number;
}

double frts::Frame::getRunTime() const
{
    return runTime;
}
