#include "Application.h"

#include "configuration/ConfigNode.h"
#include "configuration/yaml/YamlConfigParser.h"

frts::Application::Application()
{
}

frts::Application::LoadConfiguration frts::Application::readLoadFile(const std::string& filePath)
{
    YamlConfigParser parser;
    ConfigNodePtr node = parser.parseFile(filePath);

    LoadConfiguration result;

    // Plugins
    ConfigNodePtr subNode = node->getNode("plugins");
    for (const auto& valueNode : *subNode)
    {
        result.plugins.push_back(valueNode->getString(""));
    }

    // Render modules
    subNode = node->getNode("renderModules");
    for (const auto& valueNode : *subNode)
    {
        result.renderModules.push_back(valueNode->getString(""));
    }

    // Update modules
    subNode = node->getNode("updateModules");
    for (const auto& valueNode : *subNode)
    {
        result.updateModules.push_back(valueNode->getString(""));
    }

    // Utilities
    subNode = node->getNode("utilities");
    for (const auto& valueNode : *subNode)
    {
        result.utilities.push_back(valueNode->getString(""));
    }

    // Configurations
    subNode = node->getNode("configurations");
    for (const auto& valueNode : *subNode)
    {
        result.configurations.push_back(valueNode->getString(""));
    }

    return result;
}
