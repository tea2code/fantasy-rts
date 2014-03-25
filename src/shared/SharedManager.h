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

    /**
     * @brief Interface representing the shared manager. It gives access
     * to the shared state including data values and other modules.
     */
    class SharedManager
    {
    public:
        virtual ~SharedManager() {}

        virtual LogPtr getLog() const = 0;
    };
}

#endif // SHAREDMANAGER_H
