#ifndef FRTS_BOOLEANEVENTVALUEIMPL_H
#define FRTS_BOOLEANEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/BooleanEventValue.h>


namespace frts
{
    class BooleanEventValueImpl : public BaseEventValue<BooleanEventValue::type, BooleanEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        BooleanEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_BOOLEANEVENTVALUEIMPL_H
