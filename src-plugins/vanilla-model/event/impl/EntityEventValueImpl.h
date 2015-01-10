#ifndef FRTS_ENTITYEVENTVALUEIMPL_H
#define FRTS_ENTITYEVENTVALUEIMPL_H

#include <frts/vanillaevent>
#include <event/EntityEventValue.h>
#include <main/impl/BaseEventValue.h>


namespace frts
{
    class EntityEventValueImpl : public BaseEventValue<EntityEventValue::type, EntityEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        EntityEventValueImpl(IdPtr type);
    };
}

#endif // FRTS_ENTITYEVENTVALUEIMPL_H
