#include "Tickable.h"

Tickable::Tickable()
{
}

void Tickable::createData(frts::SharedManagerPtr)
{

}

std::string Tickable::getName() const
{
    return "TestTickable";
}

std::vector<std::string> Tickable::getSupportedConfig()
{
    return std::vector<std::string>();
}

int Tickable::getVersion() const
{
    return 1;
}

void Tickable::init(frts::SharedManagerPtr)
{

}

void Tickable::parseConfig(frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

void Tickable::tick(frts::SharedManagerPtr)
{

}

void Tickable::validateData(frts::SharedManagerPtr)
{

}

void Tickable::validateModules(frts::SharedManagerPtr)
{
    // Everything is ok.
}
