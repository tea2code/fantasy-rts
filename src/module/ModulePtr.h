#ifndef FRTS_MODULEPTR_H
#define FRTS_MODULEPTR_H

#include <memory>

namespace frts
{
    class Module;
    class Tickable;
    class Utility;

    /**
     * Pointer to Module.
     */
    using ModulePtr = std::shared_ptr<Module>;

    /**
     * Pointer to Tickable.
     */
    using TickablePtr = std::shared_ptr<Tickable>;

    /**
     * Pointer to Utility.
     */
    using UtilityPtr = std::shared_ptr<Utility>;
}

#endif // FRTS_MODULEPTR_H
