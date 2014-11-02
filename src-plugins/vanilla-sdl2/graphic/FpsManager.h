#ifndef FRTS_FPSMANAGER_H
#define FRTS_FPSMANAGER_H

#include <memory>


namespace frts
{
    /**
     * @brief Shows and limits current frame rate.
     */
    class FpsManager
    {
    public:
        FpsManager();

        /**
         * @brief Calculates the current frame rate.
         * @return The frame rate per second.
         */
        double calcFps();

        /**
         * @brief Limits the frame rate to the given value.
         * @param fps The target frame rate.
         */
        void limitFps(double fps);

    private:
        unsigned int lastFps;
        unsigned int lastTime;
    };
}

#endif // FRTS_FPSMANAGER_H
