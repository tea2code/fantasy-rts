#include "PluginManager.h"

#include "Plugin.h"
#include "PluginError.h"

#include <boost/format.hpp>

const int frts::PluginManager::supportedVersion = 1;

frts::PluginManager::PluginManager()
{
}

frts::PluginManager::~PluginManager()
{
    // First free all plugin pointers...
    for (auto& plugin : plugins)
    {
        plugin.reset();
    }

    // ...then we can unload the library handles.
    LibraryLoader loader;
    for (auto& handle : libraryHandles)
    {
        try
        {
            loader.unload(handle);
        }
        catch(std::runtime_error)
        {
            // Shit. Hopefully the rest can be unloaded.
        }
    }
}

frts::ModulePtr frts::PluginManager::findModule(IdPtr id) noexcept
{
    ModulePtr result = nullptr;
    for (auto& plugin : plugins)
    {
        result = plugin->getModule(id);
        if (result != nullptr)
        {
            break;
        }
    }
    return result;
}


void frts::PluginManager::loadPlugin(const std::string& path, const std::string& name)
{
    LibraryLoader loader;

    // Try to load library.
    LibraryLoader::HandleType handle;
    try
    {
        handle = loader.load(path, name);
    }
    catch(std::runtime_error e)
    {
        // Library doesn't exist.
        throw LibraryNotFound(e.what());
    }

    // Prepare doesn't implement plugin api error.
    auto msg = boost::format(R"(Library "%1%" in path "%2%" doesn't implement the plugin API.)")
            % name % path;

    // Try get plugin version and check it.
    try
    {
        GetVersionFunction* pluginVersion = loader.getFunctionPointer<GetVersionFunction>(handle, "getVersion");
        if (supportedVersion != pluginVersion())
        {
            loader.unload(handle);
            throw LibraryOutDated(msg.str());
        }
    }
    catch(std::runtime_error)
    {
        // This is not a plugin library.
        loader.unload(handle);
        throw LibraryNotFound(msg.str());
    }

    // Try get plugin.
    try
    {
        GetPluginFunction* getPlugin = loader.getFunctionPointer<GetPluginFunction>(handle, "getPlugin");
        plugins.push_back(getPlugin());
        libraryHandles.push_back(handle);
    }
    catch(std::runtime_error)
    {
        // This is not a plugin library.
        loader.unload(handle);
        throw LibraryNotFound(msg.str());
    }
}
