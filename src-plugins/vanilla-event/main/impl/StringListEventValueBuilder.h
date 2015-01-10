#ifndef FRTS_STRINGLISTEVENTVALUEBUILDER_H
#define FRTS_STRINGLISTEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "StringListEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class StringListEventValueBuilder : public BaseEventValueBuilder<StringListEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        StringListEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new StringEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeStringListEventValueBuilder(IdPtr type)
    {
        return std::make_shared<StringListEventValueBuilder>(type);
    }
}

#endif // FRTS_STRINGLISTEVENTVALUEBUILDER_H
