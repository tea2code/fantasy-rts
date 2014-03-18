#include "YamlConfigParser.h"
#include <yaml-cpp/yaml.h>

#include <stdexcept>

frts::YamlConfigParser::YamlConfigParser()
{
}

frts::YamlConfigParser::~YamlConfigParser()
{

}

frts::ConfigNodePtr frts::YamlConfigParser::parseFile(const std::string& filePath)
{
    //YAML::Node rawNode = YAML::LoadFile(filePath);
    //throw std::runtime_error("");
    return nullptr;
}
