#ifndef FRTS_INTEGERLISTEVENTVALUEIMPL_H
#define FRTS_INTEGERLISTEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/IntegerListEventValue.h>


namespace frts
{
    class IntegerListEventValueImpl : public BaseEventValue<IntegerListEventValue::type, IntegerListEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        IntegerListEventValueImpl(IdPtr type);
    };
}

#endif // FRTS_INTEGERLISTEVENTVALUEIMPL_H
