#ifndef FRTS_PLUGIN_H
#define FRTS_PLUGIN_H

#include <module/ModulePtr.h>
#include <shared/Id.h>

namespace frts
{
    class Plugin
    {
    public:
        virtual ~Plugin()  {}

        /**
         * @brief Get a module from this plugin.
         * @param id The module id.
         * @return The module or null.
         */
        virtual ModulePtr getModule(IdPtr id) noexcept = 0;
    };
}

#endif // FRTS_PLUGIN_H
