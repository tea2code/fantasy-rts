#ifndef FRTS_DYNAMICENTITY_H
#define FRTS_DYNAMICENTITY_H

#include "Entity.h"

#include <memory>


namespace frts
{
    class DynamicEntity;

    /**
     * @brief Pointer to DynamicEntity.
     */
    using DynamicEntityPtr = std::shared_ptr<DynamicEntity>;

    /**
     * @brief Dynamic entities can most of the time move and have a certain
     *        intelligence.
     */
    class DynamicEntity : public Entity
    {
    public:
        virtual ~DynamicEntity() {}
    };
}

#endif // FRTS_DYNAMICENTITY_H
