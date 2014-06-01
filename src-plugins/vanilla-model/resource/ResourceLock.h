#ifndef FRTS_RESOURCELOCK_H
#define FRTS_RESOURCELOCK_H

#include <entity/Entity.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class ResourceLock;

    /**
     * @brief Pointer to ResourceLock.
     */
    using ResourceLockPtr = std::shared_ptr<ResourceLock>;

    /**
     * @brief Const pointer to ResourceLock.
     */
    using ConstResourceLockPtr = std::shared_ptr<const ResourceLock>;

    /**
     * @brief A resource lock prevents other entities from claiming a certain
     *        resource until it is released. Releasing can happen manually
     *        but also automatically if all instances of this lock are destroyed.
     */
    class ResourceLock
    {
    public:
        virtual ~ResourceLock() {}

        /**
         * @brief Get the resource entity.
         * @return The entity.
         */
        virtual EntityPtr getEntity() const = 0;

        /**
         * @brief Get the resource type.
         * @return The resource type.
         */
        virtual IdPtr getResourceType() const = 0;

        /**
         * @brief Check if lock is still valid. You should always do this before
         *        accessing any data of this lock. A lock becomes invalid if
         *        it is released.
         * @return True if lock is valid else false.
         */
        virtual bool isValid() const = 0;

        /**
         * @brief Release the lock. It is invalid afterwards. Accessing the entity
         *        or the resource type is undefined afterwards.
         */
        virtual void release() = 0;
    };
}

#endif // FRTS_RESOURCELOCK_H
