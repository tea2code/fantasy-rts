#ifndef FRTS_STRINGEVENTVALUEBUILDER_H
#define FRTS_STRINGEVENTVALUEBUILDER_H

#include "BaseEventValueBuilder.h"
#include "StringEventValueImpl.h"
#include <main/EventValueBuilder.h>

namespace frts
{
    class StringEventValueBuilder : public BaseEventValueBuilder<StringEventValueImpl>
    {
    public:
        /**
         * @param type The event value type.
         */
        StringEventValueBuilder(IdPtr type);
    };

    /**
     * @brief Create new StringEventValueBuilder.
     * @param type The event value type.
     * @return The event value builder.
     */
    inline EventValueBuilderPtr makeStringEventValueBuilder(IdPtr type)
    {
        return std::make_shared<StringEventValueBuilder>(type);
    }
}

#endif // FRTS_STRINGEVENTVALUEBUILDER_H
