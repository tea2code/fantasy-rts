#ifndef FRTS_ENTITYLISTEVENTVALUEIMPL_H
#define FRTS_ENTITYLISTEVENTVALUEIMPL_H

#include <frts/vanillaevent>
#include <event/EntityListEventValue.h>
#include <main/impl/BaseEventValue.h>


namespace frts
{
    class EntityListEventValueImpl : public BaseEventValue<EntityListEventValue::type, EntityListEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        EntityListEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_ENTITYLISTEVENTVALUEIMPL_H
