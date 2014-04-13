#include "YamlConfigParser.h"

#include "YamlConfigNode.h"
#include <configuration/ConfigError.h>

#include <boost/format.hpp>
#include <yaml-cpp/yaml.h>

#include <stdexcept>


frts::YamlConfigParser::YamlConfigParser()
{}

frts::YamlConfigParser::~YamlConfigParser()
{}

frts::ConfigNodePtr frts::YamlConfigParser::parseFile(const std::string& filePath)
{
    try
    {
        YAML::Node rawNode = YAML::LoadFile(filePath);
        return frts::ConfigNodePtr(new frts::YamlConfigNode(rawNode));
    }
    catch(YAML::Exception)
    {
        auto msg = boost::format(R"(File "%1%" not found.)") % filePath;
        throw frts::FileNotFoundError(msg.str());
    }
}