#include "TextMapParser.h"


frts::TextMapParser::TextMapParser()
{
}

std::string frts::TextMapParser::getSupportedConfig() const
{
    return "text_map";
}

void frts::TextMapParser::init(const SharedManagerPtr&)
{

}

frts::WriteableBlockPtr frts::TextMapParser::newBlock(const PointPtr&, const SharedManagerPtr&)
{
    return nullptr;
}

void frts::TextMapParser::parseConfig(const ConfigNodePtr&, const SharedManagerPtr&)
{

}

void frts::TextMapParser::validateData(const SharedManagerPtr&)
{

}
