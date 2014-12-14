#include "TextMapParser.h"


frts::TextMapParser::TextMapParser()
{
}

std::string frts::TextMapParser::getSupportedConfig() const
{
    return "text_map";
}

void frts::TextMapParser::init(SharedManagerPtr shared)
{

}

frts::WriteableBlockPtr frts::TextMapParser::newBlock(PointPtr pos, SharedManagerPtr shared)
{
    return nullptr;
}

void frts::TextMapParser::parseConfig(ConfigNodePtr node, SharedManagerPtr shared)
{

}

void frts::TextMapParser::validateData(SharedManagerPtr shared)
{

}
