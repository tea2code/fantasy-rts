#include "Application.h"

#include "configuration/ConfigNode.h"
#include "configuration/yaml/YamlConfigParser.h"

frts::Application::Application(LogPtr log)
    : log{log}
{
}

frts::Application::LoadConfiguration frts::Application::readLoadFile(const std::string& filePath)
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
