#ifndef PLUGINPTR_H
#define PLUGINPTR_H

#include <memory>

namespace frts
{
    class Plugin;

    /**
     * @brief Pointer to Plugin.
     */
    using PluginPtr = std::shared_ptr<Plugin>;
}

#endif // PLUGINPTR_H
