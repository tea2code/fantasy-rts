#ifndef UTILITY_H
#define UTILITY_H

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

#endif // UTILITY_H
