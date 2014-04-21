#include "Utility.h"

Utility::Utility()
{
}

void Utility::createData(frts::SharedManagerPtr)
{

}

std::string Utility::getName() const
{
    return "TestUtility";
}

std::vector<std::string> Utility::getSupportedConfig()
{
    return std::vector<std::string>();
}

void Utility::init(frts::SharedManagerPtr)
{

}

void Utility::parseConfig(frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

void Utility::validateData(frts::SharedManagerPtr)
{

}

void Utility::validateModules(frts::SharedManagerPtr)
{

}
