#include "MainLoop.h"

#include <module/Tickable.h>
#include <shared/impl/FrameImpl.h>
#include <frts/timer.h>

#include <boost/format.hpp>

#include <memory>


const std::string frts::MainLoop::logModule = "frts::MainLoop";

frts::MainLoop::MainLoop(Frame::time deltaTime, Frame::time maxFrameTime)
    : deltaTime{deltaTime}, maxFrameTime{maxFrameTime}
{
}

void frts::MainLoop::render(SharedManagerPtr shared) const
{
    assert(shared != nullptr);

    for (auto it = shared->renderModulesBegin(); it != shared->renderModulesEnd(); ++it)
    {
        (*it)->tick(shared);
    }
}

void frts::MainLoop::start(SharedManagerImplPtr shared) const
{
    assert(shared != nullptr);

    Frame::time runTime = fromMilliseconds(0);
    Frame::time currentTime = highResTime();
    Frame::time accumulator = fromMilliseconds(0);
    Frame::ticks tick = 0;

    std::string msgTemplate = R"(Frame time of %1%ms exceeded max frame time of %2%ms.)";
    std::string debugMsgTemplate = R"(Frame time of %1%ms exceeded delta frame time of %2%ms.)";

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
            shared->getLog()->info(logModule, msg.str());

            frameTime = maxFrameTime;
        }
        // For debugging.
        else if (frameTime > deltaTime)
        {
            auto msg = boost::format(debugMsgTemplate)
                    % std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count()
                    % std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();
            shared->getLog()->debug(logModule, msg.str());
        }

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime)
        {
            auto frame = std::make_shared<FrameImpl>(deltaTime, tick, runTime);
            shared->setFrame(frame);
            update(shared);
            accumulator -= deltaTime;
            runTime += deltaTime;
            tick += 1;
        }

        render(shared);
    }
}

void frts::MainLoop::update(SharedManagerPtr shared) const
{
    assert(shared != nullptr);

    for (auto it = shared->updateModulesBegin(); it != shared->updateModulesEnd(); ++it)
    {
        (*it)->tick(shared);
    }
}
