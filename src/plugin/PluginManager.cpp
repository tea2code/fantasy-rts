#include "PluginManager.h"

#include "Plugin.h"
#include "PluginError.h"
#include <shared/Id.h>

#include <boost/format.hpp>


// Also update in PluginApi.h.
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
        catch(const std::runtime_error& ex)
        {
            // Shit. Hopefully the rest can be unloaded.
        }
    }
}

frts::ModulePtr frts::PluginManager::findModule(const IdPtr& id)
{
    assert(id != nullptr);

    ModulePtr result = nullptr;
    for (auto& plugin : plugins)
    {
        result = plugin->getModule(id);
        if (result != nullptr)
        {
            break;
        }
    }
    if (result == nullptr)
    {
        auto msg = boost::format(R"(PluginManager: Module "%1%" not found.)")
                % id->toString();
        throw ModuleNotFound(msg.str());
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
    catch(const std::runtime_error& e)
    {
        // Library doesn't exist.
        auto msg = boost::format(R"(PluginManager: %1%)") % e.what();
        throw LibraryNotFound(msg.str());
    }

    // Try get plugin version and check it.
    try
    {
        GetVersionFunction* pluginVersion = loader.getFunctionPointer<GetVersionFunction>(handle, "getVersion");
        if (supportedVersion != pluginVersion())
        {
            loader.unload(handle);
            auto msg = boost::format(R"(PluginManager: Library "%1%" in path "%2%" implements an out-dated version of the plugin API.)")
                    % name % path;
            throw LibraryOutDated(msg.str());
        }
    }
    catch(const std::runtime_error&)
    {
        // This is not a plugin library.
        return;
    }

    // Try get plugin.
    try
    {
        GetPluginFunction* getPlugin = loader.getFunctionPointer<GetPluginFunction>(handle, "getPlugin");
        plugins.push_back(getPlugin());
        libraryHandles.push_back(handle);
    }
    catch(const std::runtime_error&)
    {
        // This is not a plugin library.
        return;
    }
}
