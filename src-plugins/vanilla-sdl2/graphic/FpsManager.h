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

    /**
     * @brief Create new FpsManager.
     * @return The FpsManager.
     */
    inline FpsManagerPtr makeFpsManager()
    {
        return std::make_shared<FpsManager>();
    }
}

#endif // FRTS_FPSMANAGER_H
