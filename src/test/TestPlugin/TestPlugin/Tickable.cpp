#include "Tickable.h"

#include "DataValue.h"

#include <frts/shared>

# include <memory>

Tickable::Tickable()
{
}

void Tickable::createData(frts::SharedManagerPtr shared)
{
    frts::DataValuePtr data = std::make_shared<DataValue>();
    frts::IdPtr id = shared->makeId(data->getName());
    shared->setDataValue(id, data);
}

std::string Tickable::getName() const
{
    return "TestTickable";
}

std::vector<std::string> Tickable::getSupportedConfig()
{
    return {"ConfigKey1", "ConfigKey2"};
}

int Tickable::getVersion() const
{
    return 1;
}

void Tickable::init(frts::SharedManagerPtr)
{

}

void Tickable::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
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
