#ifndef FRTS_FLOATEVENTVALUEIMPL_H
#define FRTS_FLOATEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/FloatEventValue.h>


namespace frts
{
    class FloatEventValueImpl : public BaseEventValue<FloatEventValue::type, FloatEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        FloatEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_FLOATEVENTVALUEIMPL_H
