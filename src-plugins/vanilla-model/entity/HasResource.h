#ifndef FRTS_HASRESOURCE_H
#define FRTS_HASRESOURCE_H

#include "Component.h"

#include <memory>


namespace frts
{
    class HasResource;

    /**
     * @brief Pointer to HasResource.
     */
    using HasResourcePtr = std::shared_ptr<HasResource>;

    /**
     * @brief Component describing if an entity has a certain resource.
     */
    class HasResource : public Component
    {
    public:
        using ResourceSet = IdUnorderedSet;

    public:
        virtual ~HasResource() {}

        /**
         * @brief Add resource.
         * @param resourceType The resource type.
         */
        virtual void addResource(const IdPtr& resourceType) = 0;

        /**
         * @brief Get all resources.
         * @return The resources.
         */
        virtual ResourceSet getResources() const = 0;

        /**
         * @brief Check if entity has resource.
         * @param resourceType The resource type.
         * @return
         */
        virtual bool hasResource(const IdPtr& resourceType) const = 0;

        /**
         * @brief Remove the resource.
         * @param resourceType The resource type.
         */
        virtual void removeResource(const IdPtr& resourceType) = 0;
    };
}

#endif // FRTS_HASRESOURCE_H
