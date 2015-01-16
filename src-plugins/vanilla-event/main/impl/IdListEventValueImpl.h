#ifndef FRTS_IDLISTEVENTVALUEIMPL_H
#define FRTS_IDLISTEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/IdListEventValue.h>


namespace frts
{
    class IdListEventValueImpl : public BaseEventValue<IdListEventValue::type, IdListEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        IdListEventValueImpl(const IdPtr& type);
    };
}

#endif // FRTS_IDLISTEVENTVALUEIMPL_H
