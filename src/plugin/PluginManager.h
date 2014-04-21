#ifndef FRTS_PLUGINMANAGER_H
#define FRTS_PLUGINMANAGER_H

#include "LibraryLoader.h"
#include "PluginPtr.h"

#include <module/ModulePtr.h>
#include <shared/SharedPtr.h>

#include <string>
#include <vector>

namespace frts
{
    /**
     * @brief The PluginManager handles loading libraries and finding modules.
     */
    class PluginManager
    {
    public:
        PluginManager();
        virtual ~PluginManager();

        /**
         * @brief Finds modules in the loaded plugins.
         * @param id The module id.
         * @return The module or null.
         */
        virtual ModulePtr findModule(IdPtr id);

        /**
         * @brief Loads a plugin defined by given path and library name.
         * @throws LibraryNotFound if the library was not found.
         * @throws LibraryOutDated if the library version is out dated.
         * @param path The directory path where the library is. Must end with slash.
         * @param name The name of the library without extension.
         */
        virtual void loadPlugin(const std::string& path, const std::string& name);

        // TODO Deactivate copy and move constructors for PluginManager?

    private:
        typedef frts::PluginPtr GetPluginFunction();
        typedef int GetVersionFunction();

    private:
        const static int supportedVersion;

        std::vector<LibraryLoader::HandleType> libraryHandles;
        std::vector<PluginPtr> plugins;
    };
}

#endif // FRTS_PLUGINMANAGER_H
