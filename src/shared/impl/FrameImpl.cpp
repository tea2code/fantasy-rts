#include "FrameImpl.h"


frts::FrameImpl::FrameImpl(time deltaTime, ticks number, time runTime)
    : deltaTime{deltaTime}, number{number}, runTime{runTime}
{
}

frts::FrameImpl::~FrameImpl()
{
}

frts::Frame::time frts::FrameImpl::getDeltaTime() const
{
    return deltaTime;
}

frts::Frame::ticks frts::FrameImpl::getNumber() const
{
    return number;
}

frts::Frame::time frts::FrameImpl::getRunTime() const
{
    return runTime;
}


frts::Frame::time frts::fromMilliseconds(unsigned int ms)
{
    return std::chrono::duration_cast<Frame::time>(std::chrono::milliseconds(ms));
}
