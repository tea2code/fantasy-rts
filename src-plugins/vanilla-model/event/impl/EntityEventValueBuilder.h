#ifndef FRTS_ENTITYEVENTVALUEBUILDER_H
#define FRTS_ENTITYEVENTVALUEBUILDER_H

#include "EntityEventValueImpl.h"
#include <frts/vanillaevent>
#include <main/impl/BaseEventValueBuilder.h>

namespace frts
{
    class EntityEventValueBuilder : public BaseEventValueBuilder<EntityEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        EntityEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new EntityEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeEntityEventValueBuilder(IdPtr type)
    {
        return std::make_shared<EntityEventValueBuilder>(type);
    }
}

#endif // FRTS_ENTITYEVENTVALUEBUILDER_H
