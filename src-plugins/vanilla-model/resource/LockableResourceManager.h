#ifndef FRTS_LOCKABLERESOURCEMANAGER_H
#define FRTS_LOCKABLERESOURCEMANAGER_H

#include "ResourceLock.h"

#include <entity/Entity.h>
#include <region/Point.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class LockableResourceManager;

    /**
     * @brief Pointer to LockableResourceManager.
     */
    using LockableResourceManagerPtr = std::shared_ptr<LockableResourceManager>;

    /**
     * @brief A LockableResourceManager allows to search for resources. If one is
     *        found it will be locked. This means that further searches won't find
     *        it until it is released or removed.
     */
    class LockableResourceManager
    {
    public:
        virtual ~LockableResourceManager() {}

        /**
         * @brief Add an entity to the resource manager.
         * @param entity The entity.
         */
        virtual void add(EntityPtr entity) = 0;

        /**
         * @brief Find nearest resource.
         * @param entityGroup The entity group for which this resource is locked.
         * @param resourceType The resource type.
         * @param pos The start position.
         * @return Lock to nearest resource or null.
         */
        virtual ResourceLockPtr findNearest(IdPtr entityGroup, IdPtr resourceType, PointPtr pos) = 0;

        /**
         * @brief Get entity of lock.
         * @param lock The resource lock.
         * @return The entity or null if lock is invalid.
         */
        virtual EntityPtr getEntity(ResourceLockPtr lock) const = 0;

        /**
         * @brief Get resource type of lock.
         * @param lock The resource lock.
         * @return The resource type or null if lock is invalid.
         */
        virtual IdPtr getResourceType(ResourceLockPtr lock) const = 0;

        /**
         * @brief Check if resource lock is still valid.
         * @param lock The resource lock.
         * @return True if lock is valid else false.
         */
        virtual bool isValid(ResourceLockPtr lock) const = 0;

        /**
         * @brief Release the lock.
         * @param lock The resource lock.
         */
        virtual void release(ResourceLockPtr lock) = 0;

        /**
         * @brief Remove an entity from the resource manager. This will also release
         *        any lock.
         * @param entity The entity.
         */
        virtual void remove(EntityPtr entity) = 0;
    };
}

#endif // FRTS_LOCKABLERESOURCEMANAGER_H
