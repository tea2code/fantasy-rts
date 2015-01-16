#ifndef FRTS_BOOLEANLISTEVENTVALUEIMPL_H
#define FRTS_BOOLEANLISTEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/BooleanListEventValue.h>


namespace frts
{
    class BooleanListEventValueImpl : public BaseEventValue<BooleanListEventValue::type, BooleanListEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        BooleanListEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_BOOLEANLISTEVENTVALUEIMPL_H
