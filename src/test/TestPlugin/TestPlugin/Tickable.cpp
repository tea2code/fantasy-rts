#include "Tickable.h"

#include "DataValue.h"

#include <frts/shared>

# include <memory>

Tickable::Tickable()
{
}

bool Tickable::createData(frts::SharedManagerPtr shared)
{
    auto data = std::make_shared<DataValue>();
    auto id = shared->makeId(data->getName());
    shared->setDataValue(id, data);

    return false;
}

std::string Tickable::getName() const
{
    return "TestTickable";
}

std::vector<std::string> Tickable::getSupportedConfig()
{
    return {"ConfigKey1", "ConfigKey2"};
}

std::string Tickable::getTypeName() const
{
    return getName();
}

int Tickable::getTypeVersion() const
{
    return getVersion();
}

int Tickable::getVersion() const
{
    return 1;
}

bool Tickable::init(frts::SharedManagerPtr)
{
    return false;
}

void Tickable::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

bool Tickable::preInit(frts::SharedManagerPtr)
{
    return false;
}

void Tickable::tick(frts::SharedManagerPtr)
{

}

void Tickable::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
}

void Tickable::validateModules(frts::SharedManagerPtr)
{
    // Everything is ok.
}
