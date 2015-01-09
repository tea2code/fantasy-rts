#ifndef FRTS_ENTITYLISTEVENTVALUEBUILDER_H
#define FRTS_ENTITYLISTEVENTVALUEBUILDER_H

#include "EntityListEventValueImpl.h"
#include <frts/vanillaevent>
#include <main/impl/BaseEventValueBuilder.h>

namespace frts
{
    class EntityListEventValueBuilder : public BaseEventValueBuilder<EntityListEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        EntityListEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new EntityListEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeEntityListEventValueBuilder(IdPtr type)
    {
        return std::make_shared<EntityListEventValueBuilder>(type);
    }
}

#endif // FRTS_ENTITYLISTEVENTVALUEBUILDER_H
