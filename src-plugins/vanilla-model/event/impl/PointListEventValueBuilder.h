#ifndef FRTS_POINTLISTEVENTVALUEBUILDER_H
#define FRTS_POINTLISTEVENTVALUEBUILDER_H

#include "PointListEventValueImpl.h"
#include <frts/vanillaevent>
#include <main/impl/BaseEventValueBuilder.h>

namespace frts
{
    class PointListEventValueBuilder : public BaseEventValueBuilder<PointListEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        PointListEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new PointListEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makePointListEventValueBuilder(IdPtr type)
    {
        return std::make_shared<PointListEventValueBuilder>(type);
    }
}

#endif // FRTS_POINTLISTEVENTVALUEBUILDER_H
