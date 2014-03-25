#include "FrameImpl.h"

frts::FrameImpl::FrameImpl(double deltaTime, unsigned long long number, double runTime)
    : deltaTime{deltaTime}, number{number}, runTime{runTime}
{
}

frts::FrameImpl::~FrameImpl()
{
}

double frts::FrameImpl::getDeltaTime() const
{
    return deltaTime;
}

unsigned long long frts::FrameImpl::getNumber() const
{
    return number;
}

double frts::FrameImpl::getRunTime() const
{
    return runTime;
}
