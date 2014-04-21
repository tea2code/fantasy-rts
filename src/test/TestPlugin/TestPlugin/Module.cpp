#include "Module.h"

Module::Module()
{
}

void Module::createData(frts::SharedManagerPtr)
{

}

std::string Module::getName() const
{
    return "TestModule";
}

std::vector<std::string> Module::getSupportedConfig()
{
    return std::vector<std::string>();
}

void Module::init(frts::SharedManagerPtr)
{

}

void Module::parseConfig(frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

void Module::tick(frts::SharedManagerPtr)
{

}

void Module::validateData(frts::SharedManagerPtr)
{

}

void Module::validateModules(frts::SharedManagerPtr)
{

}
