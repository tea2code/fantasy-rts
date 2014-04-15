#ifndef FRTS_UTILITY_H
#define FRTS_UTILITY_H

#include "Module.h"


namespace frts
{
    /**
     * @brief Interface for utitlity modules.
     */
    class Utility : public Module
    {
    public:
        virtual ~Utility() {}
    };
}

#endif // FRTS_UTILITY_H
