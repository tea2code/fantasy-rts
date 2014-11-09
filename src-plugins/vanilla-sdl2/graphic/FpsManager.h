#ifndef FRTS_FPSMANAGER_H
#define FRTS_FPSMANAGER_H

#include <memory>
#include <list>


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
        unsigned int calcFps();

        /**
         * @brief Limits the frame rate to the given value.
         * @param fps The target frame rate.
         */
        void limitFps(unsigned int fps);

        /**
         * @brief Set number of fps measures to calculate fps.
         * @param numFpsAvg The number of fps measures used.
         */
        void setNumFpsAvg(unsigned int numFpsAvg = 1);

    private:
        std::list<unsigned int> fpsQueue;
        unsigned int lastLimitTime;
        unsigned int lastTime;
        unsigned int numFpsAvg;
    };
}

#endif // FRTS_FPSMANAGER_H
