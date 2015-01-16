#include "MainLoop.h"

#include <module/Tickable.h>
#include <shared/impl/FrameImpl.h>
#include <frts/timer.h>

#include <boost/format.hpp>


frts::MainLoop::MainLoop(Frame::time deltaTime, Frame::time maxFrameTime)
    : deltaTime{deltaTime}, maxFrameTime{maxFrameTime}
{
}

void frts::MainLoop::render(const SharedManagerPtr& shared) const
{
    assert(shared != nullptr);

    for (auto it = shared->renderModulesBegin(); it != shared->renderModulesEnd(); ++it)
    {
        (*it)->tick(shared);
    }
}

void frts::MainLoop::start(const SharedManagerImplPtr& shared) const
{
    assert(shared != nullptr);

    Frame::time runTime = fromMilliseconds(0);
    Frame::time currentTime = highResTime();
    Frame::time accumulator = fromMilliseconds(0);
    Frame::ticks tick = 0;

    Frame::time deltaTimeDebug = deltaTime + fromMilliseconds(1);

    std::string maxFrameTimeWarnMsg = R"(Frame %3% exceeded frame time of %1%ms with max frame time of %2%ms.)";
    std::string frameTimeWarnMsg = R"(Frame %3% exceeded frame time of %1%ms with delta frame time of %2%ms.)";

    auto frame = makeFrame(deltaTime, tick, runTime);
    shared->setFrame(frame);

    while (!shared->isQuitApplication())
    {
        Frame::time newTime = highResTime();

        // Limit frame time to a maximum to avoid spiral of death.
        Frame::time frameTime = newTime - currentTime;
        if (frameTime > maxFrameTime)
        {
            auto msg = boost::format(maxFrameTimeWarnMsg)
                    % std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count()
                    % std::chrono::duration_cast<std::chrono::milliseconds>(maxFrameTime).count()
                    % frame->getNumber();
            shared->getLog()->info(logModule, msg.str());

            frameTime = maxFrameTime;
        }
        // For debugging.
        else if (frameTime > deltaTimeDebug)
        {
            auto msg = boost::format(frameTimeWarnMsg)
                    % std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count()
                    % std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count()
                    % frame->getNumber();
            shared->getLog()->debug(logModule, msg.str());
        }

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime)
        {
            frame = makeFrame(deltaTime, tick, runTime);
            shared->setFrame(frame);
            update(shared);
            accumulator -= deltaTime;
            runTime += deltaTime;
            tick += 1;
        }

        render(shared);
    }
}

void frts::MainLoop::update(const SharedManagerPtr& shared) const
{
    assert(shared != nullptr);

    for (auto it = shared->updateModulesBegin(); it != shared->updateModulesEnd(); ++it)
    {
        (*it)->tick(shared);
    }
}
