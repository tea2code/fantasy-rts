#ifndef FRTS_PLUGINPTR_H
#define FRTS_PLUGINPTR_H

#include <memory>

namespace frts
{
    class Plugin;

    /**
     * @brief Pointer to Plugin.
     */
    using PluginPtr = std::shared_ptr<Plugin>;
}

#endif // FRTS_PLUGINPTR_H
