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
        virtual ~HasResource() {}
    };
}

#endif // FRTS_HASRESOURCE_H
