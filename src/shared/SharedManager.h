#ifndef SHAREDMANAGER_H
#define SHAREDMANAGER_H

#include <log/Log.h>

#include <memory>

namespace frts
{
    class SharedManager;

    /**
     * Pointer to SharedManager.
     */
    using SharedManagerPtr = std::shared_ptr<SharedManager>;

    class SharedManager
    {
    public:
        virtual ~SharedManager() {}

        virtual LogPtr getLog() const = 0;
    };
}

#endif // SHAREDMANAGER_H
