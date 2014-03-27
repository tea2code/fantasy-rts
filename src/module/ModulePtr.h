#ifndef MODULEPTR_H
#define MODULEPTR_H

#include <memory>

namespace frts
{
    class Tickable;
    class Utility;

    /**
     * Pointer to Tickable.
     */
    using TickablePtr = std::shared_ptr<Tickable>;

    /**
     * Pointer to Utility.
     */
    using UtilityPtr = std::shared_ptr<Utility>;
}

#endif // MODULEPTR_H
