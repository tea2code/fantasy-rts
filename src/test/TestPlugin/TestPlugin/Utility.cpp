#include "Utility.h"

Utility::Utility()
{
}

bool Utility::createData(frts::SharedManagerPtr)
{
    return false;
}

std::string Utility::getName() const
{
    return "TestUtility";
}

std::vector<std::string> Utility::getSupportedConfig()
{
    return {"ConfigKey1", "ConfigKey3"};
}

int Utility::getVersion() const
{
    return 1;
}

bool Utility::init(frts::SharedManagerPtr)
{
    return false;
}

void Utility::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

bool Utility::preInit(frts::SharedManagerPtr)
{
    return false;
}

void Utility::validateData(frts::SharedManagerPtr)
{
    // I miss something.
    throw frts::DataViolation("I miss something.");
}

void Utility::validateModules(frts::SharedManagerPtr)
{
    // I miss something.
    throw frts::ModuleViolation("I miss something.");
}
