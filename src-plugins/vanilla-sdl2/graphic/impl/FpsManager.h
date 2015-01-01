#ifndef FRTS_FPSMANAGER_H
#define FRTS_FPSMANAGER_H

#include <frts/shared>

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
         * @param deltaTime The time of one frame.
         */
        void limitFps(Frame::time deltaTime);

        /**
         * @brief Set number of fps measures to calculate fps.
         * @param numFpsAvg The number of fps measures used.
         */
        void setNumFpsAvg(unsigned int numFpsAvg = 1);

    private:
        std::list<unsigned int> fpsQueue;
        unsigned int fpsTotal = 0;
        unsigned int lastLimitTime;
        unsigned int lastTime;
        unsigned int numFpsAvg;
    };
}

#endif // FRTS_FPSMANAGER_H
