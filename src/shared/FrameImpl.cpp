#include "FrameImpl.h"


frts::FrameImpl::FrameImpl(double deltaTime, unsigned long long number, double runTime)
    : deltaTime{deltaTime}, number{number}, runTime{runTime}
{
}

frts::FrameImpl::~FrameImpl()
{
}

double frts::FrameImpl::getDeltaTime() const noexcept
{
    return deltaTime;
}

unsigned long long frts::FrameImpl::getNumber() const noexcept
{
    return number;
}

double frts::FrameImpl::getRunTime() const noexcept
{
    return runTime;
}
