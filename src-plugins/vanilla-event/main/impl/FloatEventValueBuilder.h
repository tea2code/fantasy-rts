#ifndef FRTS_FLOATEVENTVALUEBUILDER_H
#define FRTS_FLOATEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "FloatEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class FloatEventValueBuilder : public BaseEventValueBuilder<FloatEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        FloatEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new FloatEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeFloatEventValueBuilder(IdPtr type)
    {
        return std::make_shared<FloatEventValueBuilder>(type);
    }
}

#endif // FRTS_FLOATEVENTVALUEBUILDER_H
