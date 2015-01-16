#ifndef FRTS_INTEGERLISTEVENTVALUEBUILDER_H
#define FRTS_INTEGERLISTEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "IntegerListEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class IntegerListEventValueBuilder : public BaseEventValueBuilder<IntegerListEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        IntegerListEventValueBuilder(const IdPtr& type);
    };

    /**
     * @brief Create new IntegerListEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeIntegerListEventValueBuilder(const IdPtr& type)
    {
        return std::make_shared<IntegerListEventValueBuilder>(type);
    }
}

#endif // FRTS_INTEGERLISTEVENTVALUEBUILDER_H
