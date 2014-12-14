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
        auto rawNode = YAML::LoadFile(filePath);
        return std::make_shared<YamlConfigNode>(rawNode);
    }
    catch(const YAML::Exception& ex)
    {
        if (ex.msg == "bad file")
        {
            auto msg = boost::format(R"(File "%1%" not found.)") % filePath;
            throw frts::FileNotFoundError(msg.str());
        }
        else
        {
            auto msg = boost::format(R"(File "%1%" contains the error "%2%" near line %3% and column %4%.)")
                    % filePath % ex.msg % ex.mark.line % ex.mark.column;
            throw frts::FileNotParsableError(msg.str());
        }
    }
}
