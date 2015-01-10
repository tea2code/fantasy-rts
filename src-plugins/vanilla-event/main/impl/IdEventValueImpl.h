#ifndef FRTS_IDEVENTVALUEIMPL_H
#define FRTS_IDEVENTVALUEIMPL_H

#include "BaseEventValue.h"
#include <main/IdEventValue.h>


namespace frts
{
    class IdEventValueImpl : public BaseEventValue<IdEventValue::type, IdEventValue>
    {
    public:
        /**
         * @param type The event value type.
         */
        IdEventValueImpl(IdPtr type);
    };
}

#endif // FRTS_IDEVENTVALUEIMPL_H
