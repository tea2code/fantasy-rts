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
    if (!key.empty() && node.IsScalar())
    {
        throw makeMissingValueError(key);
    }
    YAML::Node valueNode = !key.empty() ? node[key] : node;
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
    if (!key.empty() && node.IsScalar())
    {
        throw makeMissingValueError(key);
    }
    YAML::Node valueNode = !key.empty() ? node[key] : node;
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
    return get<bool>(key, "boolean");
}

bool frts::YamlConfigNode::getBool(const std::string& key, bool defaultValue)
{
    return getDefault<bool>(key, defaultValue);
}

std::vector<bool> frts::YamlConfigNode::getBools(const std::string& key)
{
    frts::ConfigNodePtr listNode = getNode(key);
    std::vector<bool> result;
    for(const auto& valueNode : *listNode)
    {
        result.push_back(valueNode->getBool(""));
    }
    return result;
}

double frts::YamlConfigNode::getFloat(const std::string& key)
{
    return get<double>(key, "floating point");
}

double frts::YamlConfigNode::getFloat(const std::string& key, double defaultValue)
{
    return getDefault<double>(key, defaultValue);
}

std::vector<double> frts::YamlConfigNode::getFloats(const std::string& key)
{
    frts::ConfigNodePtr listNode = getNode(key);
    std::vector<double> result;
    for(const auto& valueNode : *listNode)
    {
        result.push_back(valueNode->getFloat(""));
    }
    return result;
}

long frts::YamlConfigNode::getInteger(const std::string& key)
{
    return get<long>(key, "integer");
}

long frts::YamlConfigNode::getInteger(const std::string& key, long defaultValue)
{
    return getDefault<long>(key, defaultValue);
}

std::vector<long> frts::YamlConfigNode::getIntegers(const std::string& key)
{
    frts::ConfigNodePtr listNode = getNode(key);
    std::vector<long> result;
    for(const auto& valueNode : *listNode)
    {
        result.push_back(valueNode->getInteger(""));
    }
    return result;
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
    return get<std::string>(key, "string");
}

std::string frts::YamlConfigNode::getString(const std::string& key,
                                            const std::string& defaultValue)
{
    return getDefault<std::string>(key, defaultValue);
}

std::vector<std::string> frts::YamlConfigNode::getStrings(const std::string& key)
{
    frts::ConfigNodePtr listNode = getNode(key);
    std::vector<std::string> result;
    for(const auto& valueNode : *listNode)
    {
        result.push_back(valueNode->getString(""));
    }
    return result;
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

bool frts::YamlConfigNode::isInteger(const std::string& key)
{
    return is<long>(key);
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
