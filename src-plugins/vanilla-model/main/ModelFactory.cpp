#include "ModelFactory.h"

#include <frts/shared>


frts::ModelFactory::ModelFactory()
{
}

bool frts::ModelFactory::createData(frts::SharedManagerPtr)
{
    return false;
}

std::string frts::ModelFactory::getName() const
{
    return "frts::ModelFactory";
}

std::vector<std::string> frts::ModelFactory::getSupportedConfig()
{
    return {};
}

int frts::ModelFactory::getVersion() const
{
    return 1;
}

bool frts::ModelFactory::init(frts::SharedManagerPtr)
{
    return false;
}

void frts::ModelFactory::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

void frts::ModelFactory::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
}

void frts::ModelFactory::validateModules(frts::SharedManagerPtr)
{
    // Everything is ok.
}
