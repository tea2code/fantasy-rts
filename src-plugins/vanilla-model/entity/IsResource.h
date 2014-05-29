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
    };
}

#endif // FRTS_ISRESOURCE_H
