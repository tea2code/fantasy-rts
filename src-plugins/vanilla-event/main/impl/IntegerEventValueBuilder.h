#ifndef FRTS_INTEGEREVENTVALUEBUILDER_H
#define FRTS_INTEGEREVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "IntegerEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class IntegerEventValueBuilder : public BaseEventValueBuilder<IntegerEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        IntegerEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new IntegerEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeIntegerEventValueBuilder(IdPtr type)
    {
        return std::make_shared<IntegerEventValueBuilder>(type);
    }
}

#endif // FRTS_INTEGEREVENTVALUEBUILDER_H
