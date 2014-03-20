#include "YamlConfigNode.h"

#include "YamlConfigNodeItr.h"
#include <configuration/ConfigError.h>
#include <IteratorWrapper.h>

#include <boost/format.hpp>

#include <stdexcept>


frts::YamlConfigNode::YamlConfigNode(const YAML::Node& node)
    : node{node}
{

}

frts::YamlConfigNode::~YamlConfigNode()
{

}

frts::ConfigNode::Iterator frts::YamlConfigNode::begin()
{
    return Iterator(new YamlConfigNodeItr(node.begin()));
}

frts::ConfigNode::Iterator frts::YamlConfigNode::end()
{
    return Iterator(new YamlConfigNodeItr(node.end()));
}

template<typename T>
T frts::YamlConfigNode::get(const std::string& key, const std::string& type)
{
    YAML::Node valueNode = node[key];
    if (valueNode)
    {
        try
        {
            return valueNode.as<T>();
        }
        catch(YAML::BadConversion)
        {
            throw makeConversionError(key, type);
        }
    }
    else
    {
        throw makeMissingValueError(key);
    }
}

template<typename T>
T frts::YamlConfigNode::getDefault(const std::string& key, T defaultValue)
{
    T result = defaultValue;
    YAML::Node valueNode = node[key];
    if (valueNode)
    {
        try
        {
            result = valueNode.as<T>();
        }
        catch(YAML::BadConversion)
        {
            // We can ignore it. Using the default value.
        }
    }
    return result;
}

bool frts::YamlConfigNode::getBool(const std::string& key)
{
    return get<bool>(key, "bool");
}

bool frts::YamlConfigNode::getBool(const std::string& key, bool defaultValue)
{
    return getDefault<bool>(key, defaultValue);
}

float frts::YamlConfigNode::getFloat(const std::string& key)
{
    return get<float>(key, "float");
}

float frts::YamlConfigNode::getFloat(const std::string& key, float defaultValue)
{
    return getDefault<float>(key, defaultValue);
}

int frts::YamlConfigNode::getInt(const std::string& key)
{
    return get<int>(key, "int");
}

int frts::YamlConfigNode::getInt(const std::string& key, int defaultValue)
{
    return getDefault<int>(key, defaultValue);
}

frts::ConfigNodePtr frts::YamlConfigNode::getNode(const std::string& key)
{
    YAML::Node rawNode = node[key];
    if (rawNode)
    {
        return ConfigNodePtr(new YamlConfigNode(rawNode));
    }
    else
    {
        throw makeMissingValueError(key);
    }
}

std::string frts::YamlConfigNode::getString(const std::string& key)
{
    return get<std::string>(key, "std::string");
}

std::string frts::YamlConfigNode::getString(const std::string& key,
                                            const std::string& defaultValue)
{
    return getDefault<std::string>(key, defaultValue);
}

bool frts::YamlConfigNode::has(const std::string& key)
{
    return node[key];
}

template<typename T>
bool frts::YamlConfigNode::is(const std::string& key)
{
    YAML::Node valueNode = node[key];
    if (valueNode)
    {
        try
        {
            // Prevent compiler from optimizing this and return true.
            T value = valueNode.as<T>();
            return value == value;
        }
        catch(YAML::BadConversion)
        {
            return false;
        }
    }
    else
    {
        throw makeMissingValueError(key);
    }
}

bool frts::YamlConfigNode::isBool(const std::string& key)
{
    return is<bool>(key);
}

bool frts::YamlConfigNode::isFloat(const std::string& key)
{
    return is<float>(key);
}

bool frts::YamlConfigNode::isInt(const std::string& key)
{
    return is<int>(key);
}

bool frts::YamlConfigNode::isString(const std::string& key)
{
    return is<std::string>(key);
}

frts::ConversionError frts::YamlConfigNode::makeConversionError(const std::string& key, const std::string& type)
{
    auto msg = boost::format(R"(Value "%1%" is not a %2%.)") % key % type;
    return frts::ConversionError(msg.str());
}

frts::MissingValueError frts::YamlConfigNode::makeMissingValueError(const std::string& key)
{
    auto msg = boost::format(R"(Value "%1%" does not exist.)") % key;
    return frts::MissingValueError(msg.str());
}
