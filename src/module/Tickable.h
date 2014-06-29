#ifndef FRTS_TICKABLE_H
#define FRTS_TICKABLE_H

#include "Module.h"


namespace frts
{
    /**
     * @brief Interface for tickable modules.
     */
    class Tickable : public Module
    {
    public:
        virtual ~Tickable() {}

        /**
         * @brief Called every frame with the currend shared state. Executed
         *        during "Startup", "Run Game" and "Shutdown" phases.
         * @param shared The shared manager.
         */
        virtual void tick(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_TICKABLE_H
