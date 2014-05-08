#ifndef FRTS_STATICENTITY_H
#define FRTS_STATICENTITY_H

#include "Entity.h"

#include <memory>


namespace frts
{
    class StaticEntity;

    /**
     * @brief Pointer to StaticEntity.
     */
    using StaticEntityPtr = std::shared_ptr<StaticEntity>;

    /**
     * @brief Static entities are inanimated objects like trees or rocks.
     */
    class StaticEntity : public Entity
    {
    public:
        virtual ~StaticEntity() {}
    };
}

#endif // FRTS_STATICENTITY_H
