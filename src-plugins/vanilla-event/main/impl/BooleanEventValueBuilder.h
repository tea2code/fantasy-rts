#ifndef FRTS_BOOLEANEVENTVALUEBUILDER_H
#define FRTS_BOOLEANEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "BooleanEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class BooleanEventValueBuilder : public BaseEventValueBuilder<BooleanEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        BooleanEventValueBuilder(const IdPtr& type);
    };

    /**
     * @brief Create new BooleanEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeBooleanEventValueBuilder(const IdPtr& type)
    {
        return std::make_shared<BooleanEventValueBuilder>(type);
    }
}

#endif // FRTS_BOOLEANEVENTVALUEBUILDER_H
