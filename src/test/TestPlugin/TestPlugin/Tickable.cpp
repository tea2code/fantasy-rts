#include "Tickable.h"

#include "DataValue.h"

#include <frts/shared>

# include <memory>

Tickable::Tickable()
{
}

void Tickable::checkRequiredData(const frts::SharedManagerPtr&)
{

}

bool Tickable::createData(const frts::SharedManagerPtr& shared)
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

bool Tickable::init(const frts::SharedManagerPtr&)
{
    return false;
}

bool Tickable::isInitialized() const
{
    return false;
}

bool Tickable::isPreInitialized() const
{
    return false;
}

void Tickable::parseConfig(const std::string&, const frts::ConfigNodePtr&, const frts::SharedManagerPtr&)
{

}

bool Tickable::preInit(const frts::SharedManagerPtr&)
{
    return false;
}

void Tickable::tick(const frts::SharedManagerPtr&)
{

}

void Tickable::validateData(const frts::SharedManagerPtr&)
{
    // Everything is ok.
}

void Tickable::validateModules(const frts::SharedManagerPtr&)
{
    // Everything is ok.
}
