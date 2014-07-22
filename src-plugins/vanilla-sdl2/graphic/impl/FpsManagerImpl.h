#ifndef FRTS_FPSMANAGERIMPL_H
#define FRTS_FPSMANAGERIMPL_H

#include <graphic/FpsManager.h>


namespace frts
{
    class FpsManagerImpl : public FpsManager
    {
    public:
        FpsManagerImpl();

        double calcFps();
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
        return std::make_shared<FpsManagerImpl>();
    }
}

#endif // FRTS_FPSMANAGERIMPL_H
