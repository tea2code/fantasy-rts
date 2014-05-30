#ifndef FRTS_ISRESOURCE_H
#define FRTS_ISRESOURCE_H

#include "Component.h"

#include <memory>


namespace frts
{
    class IsResource;

    /**
     * @brief Pointer to IsResource.
     */
    using IsResourcePtr = std::shared_ptr<IsResource>;

    /**
     * @brief Component describing is an entity represents a certain resource.
     */
    class IsResource : public Component
    {
    public:
        virtual ~IsResource() {}

        /**
         * @brief Get type of resource.
         * @return The resource type.
         */
        virtual IdPtr getResourceType() const = 0;

        /**
         * @brief Set type of resource.
         * @param resourceType The resource type.
         */
        virtual void setResourceType(IdPtr resourceType) = 0;
    };
}

#endif // FRTS_ISRESOURCE_H
