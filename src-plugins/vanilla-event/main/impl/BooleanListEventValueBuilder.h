#ifndef FRTS_BOOLEANLISTEVENTVALUEBUILDER_H
#define FRTS_BOOLEANLISTEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "BooleanListEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class BooleanListEventValueBuilder : public BaseEventValueBuilder<BooleanListEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        BooleanListEventValueBuilder(const IdPtr& type);
    };

    /**
     * @brief Create new BooleanListEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeBooleanListEventValueBuilder(const IdPtr& type)
    {
        return std::make_shared<BooleanListEventValueBuilder>(type);
    }
}

#endif // FRTS_BOOLEANLISTEVENTVALUEBUILDER_H
