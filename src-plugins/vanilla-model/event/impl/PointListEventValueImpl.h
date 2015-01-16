#ifndef FRTS_POINTLISTEVENTVALUEIMPL_H
#define FRTS_POINTLISTEVENTVALUEIMPL_H

#include <frts/vanillaevent>
#include <event/PointListEventValue.h>
#include <main/impl/BaseEventValue.h>


namespace frts
{
    class PointListEventValueImpl : public BaseEventValue<PointListEventValue::type, PointListEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        PointListEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_POINTLISTEVENTVALUEIMPL_H
