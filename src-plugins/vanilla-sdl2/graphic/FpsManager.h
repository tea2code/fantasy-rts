#ifndef FRTS_FPSMANAGER_H
#define FRTS_FPSMANAGER_H

#include <memory>


namespace frts
{
    class FpsManager;

    /**
     * @brief Pointer to FpsManager.
     */
    using FpsManagerPtr = std::shared_ptr<FpsManager>;

    /**
     * @brief Shows and limits current frame rate.
     */
    class FpsManager
    {
    public:
        virtual ~FpsManager() {}

        /**
         * @brief Calculates the current frame rate.
         * @return The frame rate per second.
         */
        virtual double calcFps() = 0;

        /**
         * @brief Limits the frame rate to the given value.
         * @param fps The target frame rate.
         */
        virtual void limitFps(double fps) = 0;
    };
}

#endif // FRTS_FPSMANAGER_H
