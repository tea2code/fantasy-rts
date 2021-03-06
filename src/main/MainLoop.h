#ifndef FRTS_MAINLOOP_H
#define FRTS_MAINLOOP_H

#include <module/ModulePtr.h>
#include <shared/Frame.h>
#include <shared/SharedPtr.h>
#include <shared/impl/SharedManagerImpl.h>

#include <vector>


namespace frts
{
    /**
     * @brief Executes the main game loop based on a semi-fixed time step.
     *        See http://gafferongames.com/game-physics/fix-your-timestep/ for more
     *        information.
     */
    class MainLoop
    {
    public:
        /**
         * @param The time a frame should take.
         * @param The maximum time an update may take before calling the renderer.
         */
        MainLoop(Frame::time deltaTime, Frame::time maxFrameTime);

        /**
         * @brief Execute the main loop.
         * @param shared The shared manager.
         */
        void start(const SharedManagerImplPtr& shared) const;

    private:
        /**
         * @brief The time a frame should take.
         */
        Frame::time deltaTime;

        /**
         * @brief The maximum time an update may take before calling the renderer.
         */
        Frame::time maxFrameTime;

    private:
        /**
         * @brief The module name for log.
         */
        const std::string logModule = "frts::MainLoop";

        /**
         * @brief Execute the render modules of the shared manager.
         * @param shared The shared manager.
         */
        void render(const SharedManagerPtr& shared) const;

        /**
         * @brief Execute the update modules of the shared manager.
         * @param shared The shared manager.
         */
        void update(const SharedManagerPtr& shared) const;
    };
}

#endif // FRTS_MAINLOOP_H
