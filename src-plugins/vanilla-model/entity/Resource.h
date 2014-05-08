#ifndef FRTS_RESOURCE_H
#define FRTS_RESOURCE_H

#include "Entity.h"

#include <memory>


namespace frts
{
    class Resource;

    /**
     * @brief Pointer to Resource.
     */
    using ResourcePtr = std::shared_ptr<Resource>;

    /**
     * @brief Represents a usable resource.
     */
    class Resource : public Entity
    {
    public:
        virtual ~Resource() {}
    };
}

#endif // FRTS_RESOURCE_H
