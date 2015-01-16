#ifndef FRTS_IDLISTEVENTVALUEBUILDER_H
#define FRTS_IDLISTEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "IdListEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class IdListEventValueBuilder : public BaseEventValueBuilder<IdListEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        IdListEventValueBuilder(const IdPtr& type);
    };

    /**
     * @brief Create new IdListEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeIdListEventValueBuilder(const IdPtr& type)
    {
        return std::make_shared<IdListEventValueBuilder>(type);
    }
}

#endif // FRTS_IDLISTEVENTVALUEBUILDER_H
