#ifndef FRTS_FLOATLISTEVENTVALUEIMPL_H
#define FRTS_FLOATLISTEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/FloatListEventValue.h>


namespace frts
{
    class FloatListEventValueImpl : public BaseEventValue<FloatListEventValue::type, FloatListEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        FloatListEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_FLOATLISTEVENTVALUEIMPL_H
