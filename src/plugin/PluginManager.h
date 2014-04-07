#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <module/ModulePtr.h>
#include <shared/Id.h>

#include <string>

namespace frts
{
    /**
     * @brief The PluginManager handles loading libraries and finding modules.
     */
    class PluginManager
    {
    public:
        PluginManager();
        virtual ~PluginManager() {}

        /**
         * @brief Finds modules in the loaded plugins.
         * @param id The module id.
         * @return The module or null.
         */
        virtual ModulePtr findModule(IdPtr id);

        /**
         * @brief Loads a plugin defined by given path and library name.
         * @param path The directory path where the library is.
         * @param name The name of the library without extension.
         */
        virtual void loadPlugin(const std::string& path, const std::string& name);
    };
}

#endif // PLUGINMANAGER_H
