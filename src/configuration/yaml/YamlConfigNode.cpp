#include "YamlConfigNode.h"
#include "IteratorWrapper.h"

#include <stdexcept>

frts::YamlConfigNode::YamlConfigNode()
{

}

frts::YamlConfigNode::~YamlConfigNode()
{

}

frts::ConfigNode::Iterator frts::YamlConfigNode::begin()
{
    throw std::runtime_error("");
}

frts::ConfigNode::Iterator frts::YamlConfigNode::end()
{
    throw std::runtime_error("");
}

bool frts::YamlConfigNode::getBool(const std::string& key)
{
    throw std::runtime_error("");
    return false;
}

bool frts::YamlConfigNode::getBool(const std::string& key, bool devaultValue)
{
    throw std::runtime_error("");
    return false;
}

float frts::YamlConfigNode::getFloat(const std::string& key)
{
    throw std::runtime_error("");
    return 0.0;
}

float frts::YamlConfigNode::getFloat(const std::string& key, float devaultValue)
{
    throw std::runtime_error("");
    return 0.0;
}

int frts::YamlConfigNode::getInt(const std::string& key)
{
    throw std::runtime_error("");
    return 0;
}

int frts::YamlConfigNode::getInt(const std::string& key, int devaultValue)
{
    throw std::runtime_error("");
    return 0;
}

frts::ConfigNodePtr frts::YamlConfigNode::getNode(const std::string& key)
{
    throw std::runtime_error("");
    return std::unique_ptr<frts::YamlConfigNode>();
}

std::string frts::YamlConfigNode::getString(const std::string& key)
{
    throw std::runtime_error("");
    return "";
}

std::string frts::YamlConfigNode::getString(const std::string& key,
                                            const std::string& devaultValue)
{
    throw std::runtime_error("");
    return "";
}

bool frts::YamlConfigNode::has(const std::string& key)
{
    throw std::runtime_error("");
    return false;
}
