#ifndef FRTS_STRINGEVENTVALUEIMPL_H
#define FRTS_STRINGEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/StringEventValue.h>


namespace frts
{
    class StringEventValueImpl : public BaseEventValue<StringEventValue::type, StringEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        StringEventValueImpl(IdPtr type);
    };
}

#endif // FRTS_STRINGEVENTVALUEIMPL_H
