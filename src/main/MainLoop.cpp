#include "MainLoop.h"

#include <module/Tickable.h>
#include <shared/impl/FrameImpl.h>

#include <boost/format.hpp>

#include <memory>


const std::string frts::MainLoop::logModule = "MainLoop";

frts::MainLoop::MainLoop(Frame::time deltaTime, Frame::time maxFrameTime)
    : deltaTime{deltaTime}, maxFrameTime{maxFrameTime}
{
}

frts::Frame::time frts::MainLoop::highResTime() const
{
    auto now = std::chrono::high_resolution_clock::now();
    auto timeSinceEpoch = now.time_since_epoch();
    return std::chrono::duration_cast<Frame::time>(timeSinceEpoch);
}

void frts::MainLoop::render(SharedManagerPtr shared) const
{
    for (auto it = shared->renderModulesBegin(); it != shared->renderModulesEnd(); ++it)
    {
        (*it)->tick(shared);
    }
}


void frts::MainLoop::start(SharedManagerImplPtr shared) const
{
    Frame::time runTime = fromMilliseconds(0);
    Frame::time currentTime = highResTime();
    Frame::time accumulator = fromMilliseconds(0);
    Frame::ticks tick = 0;

    std::string msgTemplate = R"(Frame time of %1%ms exceeded max frame time of %2%ms.)";

    while (!shared->isQuitApplication())
    {
        Frame::time newTime = highResTime();

        // Limit frame time to a maximum to avoid spiral of death.
        Frame::time frameTime = newTime - currentTime;
        if (frameTime > maxFrameTime)
        {
            auto msg = boost::format(msgTemplate)
                    % std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count()
                    % std::chrono::duration_cast<std::chrono::milliseconds>(maxFrameTime).count();
            shared->getLog()->warning(logModule, msg.str());

            frameTime = maxFrameTime;
        }

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime)
        {
            FramePtr frame = std::make_shared<FrameImpl>(deltaTime, tick, runTime);
            shared->setFrame(frame);
            update(shared);
            accumulator -= deltaTime;
            runTime += deltaTime;
            tick += 1;
        }

        FramePtr frame = std::make_shared<FrameImpl>(deltaTime, tick, runTime);
        shared->setFrame(frame);
        render(shared);
    }
}

void frts::MainLoop::update(SharedManagerPtr shared) const
{
    for (auto it = shared->updateModulesBegin(); it != shared->updateModulesEnd(); ++it)
    {
        (*it)->tick(shared);
    }
}