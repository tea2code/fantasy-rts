#ifndef FRTS_POINTEVENTVALUEBUILDER_H
#define FRTS_POINTEVENTVALUEBUILDER_H

#include "PointEventValueImpl.h"
#include <frts/vanillaevent>
#include <main/impl/BaseEventValueBuilder.h>

namespace frts
{
    class PointEventValueBuilder : public BaseEventValueBuilder<PointEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        PointEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new PointEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makePointEventValueBuilder(IdPtr type)
    {
        return std::make_shared<PointEventValueBuilder>(type);
    }
}

#endif // FRTS_POINTEVENTVALUEBUILDER_H
