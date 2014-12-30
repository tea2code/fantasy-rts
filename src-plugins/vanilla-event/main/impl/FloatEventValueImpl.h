#ifndef FRTS_FLOATEVENTVALUEIMPL_H
#define FRTS_FLOATEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/FloatEventValue.h>


namespace frts
{
    class FloatEventValueImpl : public BaseEventValue<double, FloatEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        FloatEventValueImpl(IdPtr type);
    };
}

#endif // FRTS_FLOATEVENTVALUEIMPL_H