#ifndef FRTS_FLOATLISTEVENTVALUEBUILDER_H
#define FRTS_FLOATLISTEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "FloatListEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class FloatListEventValueBuilder : public BaseEventValueBuilder<FloatListEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        FloatListEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new FloatListEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeFloatListEventValueBuilder(IdPtr type)
    {
        return std::make_shared<FloatListEventValueBuilder>(type);
    }
}

#endif // FRTS_FLOATLISTEVENTVALUEBUILDER_H
