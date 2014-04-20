#include "Application.h"

#include <configuration/ConfigNode.h>
#include <configuration/yaml/YamlConfigParser.h>
#include <plugin/PluginManager.h>


frts::Application::Application(LogPtr log)
    : log{log}
{
}

std::vector<frts::PluginPtr> frts::Application::loadPlugins(const std::vector<std::string>& pluginPaths) const
{
    PluginManager pluginManager;

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
