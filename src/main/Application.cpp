#include "Application.h"

#include <configuration/ConfigNode.h>
#include <configuration/yaml/YamlConfigParser.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/impl/IdImpl.h>

#include <algorithm>
#include <string>


frts::Application::Application(LogPtr log)
    : log{log}
{
}

std::vector<frts::TickablePtr> frts::Application::findTickables(const std::vector<std::string>& moduleNames)
{
    std::vector<TickablePtr> result;
    for(const auto& moduleName : moduleNames)
    {
        IdPtr id = makeId(moduleName);
        TickablePtr module = std::dynamic_pointer_cast<Tickable>(pluginManager.findModule(id));
        result.push_back(module);
    }
    return result;
}

std::vector<frts::UtilityPtr> frts::Application::findUtilities(const std::vector<std::string>& moduleNames)
{
    std::vector<UtilityPtr> result;
    for(const auto& moduleName : moduleNames)
    {
        IdPtr id = makeId(moduleName);
        UtilityPtr module = std::dynamic_pointer_cast<Utility>(pluginManager.findModule(id));
        result.push_back(module);
    }
    return result;
}

void frts::Application::loadPlugins(const std::string& rootPath,
                                    const std::vector<std::string>& pluginPaths)
{
    for(const auto& pluginPath : pluginPaths)
    {
        // Normalize path.
        std::string path = rootPath + pluginPath;
        std::replace(path.begin(), path.end(), '\\', '/');

        // Split path into path and library name.
        std::string name;
        std::string::size_type index = path.find_last_of('/');
        if (index != std::string::npos)
        {
            index += 1;
            name = path.substr(index, path.size() - index);
            path = path.substr(0, index);
        }
        else
        {
            name = path;
            path = "";
        }

        // Load plugin.
        pluginManager.loadPlugin(path, name);
    }
}

frts::Application::LoadConfiguration frts::Application::readLoadFile(const std::string& filePath) const
{
    YamlConfigParser parser;
    ConfigNodePtr node = parser.parseFile(filePath);

    LoadConfiguration result;
    result.plugins = node->getStrings("plugins");
    result.renderModules = node->getStrings("renderModules");
    result.updateModules = node->getStrings("updateModules");
    result.utilities = node->getStrings("utilities");
    result.configurations = node->getStrings("configurations");
    return result;
}
