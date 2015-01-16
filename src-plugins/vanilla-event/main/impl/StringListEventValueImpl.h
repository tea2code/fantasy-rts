#ifndef FRTS_STRINGLISTEVENTVALUEIMPL_H
#define FRTS_STRINGLISTEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/StringListEventValue.h>


namespace frts
{
    class StringListEventValueImpl : public BaseEventValue<StringListEventValue::type, StringListEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        StringListEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_STRINGLISTEVENTVALUEIMPL_H
