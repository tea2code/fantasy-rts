#ifndef TICKABLE_H
#define TICKABLE_H

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
         * @brief Called every frame with the currend shared state.
         * @param shared The shared manager.
         */
        virtual void tick(SharedManagerPtr shared) = 0;
    };
}

#endif // TICKABLE_H
