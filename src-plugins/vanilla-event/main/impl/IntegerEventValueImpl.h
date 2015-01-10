#ifndef FRTS_INTEGEREVENTVALUEIMPL_H
#define FRTS_INTEGEREVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/IntegerEventValue.h>


namespace frts
{
    class IntegerEventValueImpl : public BaseEventValue<IntegerEventValue::type, IntegerEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        IntegerEventValueImpl(IdPtr type);
    };
}

#endif // FRTS_INTEGEREVENTVALUEIMPL_H
