#ifndef FRTS_IDEVENTVALUEBUILDER_H
#define FRTS_IDEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "IdEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class IdEventValueBuilder : public BaseEventValueBuilder<IdEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        IdEventValueBuilder(const IdPtr& type);
    };

    /**
     * @brief Create new IdEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeIdEventValueBuilder(const IdPtr& type)
    {
        return std::make_shared<IdEventValueBuilder>(type);
    }
}

#endif // FRTS_IDEVENTVALUEBUILDER_H
