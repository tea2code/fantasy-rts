#ifndef FRTS_POINTEVENTVALUEIMPL_H
#define FRTS_POINTEVENTVALUEIMPL_H

#include <frts/vanillaevent>
#include <event/PointEventValue.h>
#include <main/impl/BaseEventValue.h>


namespace frts
{
    class PointEventValueImpl : public BaseEventValue<PointEventValue::type, PointEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        PointEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_POINTEVENTVALUEIMPL_H
