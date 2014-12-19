#include "TextMapParser.h"


frts::TextMapParser::TextMapParser()
{
}

std::string frts::TextMapParser::getSupportedConfig() const
{
    return "text_map";
}

void frts::TextMapParser::init(SharedManagerPtr)
{

}

frts::WriteableBlockPtr frts::TextMapParser::newBlock(PointPtr, SharedManagerPtr)
{
    return nullptr;
}

void frts::TextMapParser::parseConfig(ConfigNodePtr, SharedManagerPtr)
{

}

void frts::TextMapParser::validateData(SharedManagerPtr)
{

}
