#ifndef SHAREDMANAGER_H
#define SHAREDMANAGER_H

#include <log/Log.h>

namespace frts
{
    class SharedManager
    {
    public:
        virtual ~SharedManager() {}

        virtual LogPtr getLog() const = 0;
    };
}

#endif // SHAREDMANAGER_H
