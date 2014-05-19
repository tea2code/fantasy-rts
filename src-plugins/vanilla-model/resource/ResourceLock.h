#ifndef FRTS_RESOURCELOCK_H
#define FRTS_RESOURCELOCK_H

#include <region/Point.h>

#include <memory>


namespace frts
{
    class ResourceLock;

    /**
     * @brief Pointer to ResourceLock.
     */
    using ResourceLockPtr = std::shared_ptr<ResourceLock>;

    /**
     * @brief A resource lock prevents other entities from claiming a certain
     *        resource until it is released.
     */
    class ResourceLock
    {
    public:
        virtual ~ResourceLock() {}

        /**
         * @brief Prevent copying locks.
         */
        ResourceLock(const ResourceLock&) = delete;

        /**
         * @brief Get position of resource.
         * @return The position.
         */
        PointPtr getPos() const;
    };
}

#endif // FRTS_RESOURCELOCK_H
