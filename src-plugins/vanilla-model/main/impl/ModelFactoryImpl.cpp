#include "ModelFactoryImpl.h"

#include <region/impl/PointImpl.h>

#include <frts/shared>

#include <memory>


frts::ModelFactoryImpl::ModelFactoryImpl()
{
}

bool frts::ModelFactoryImpl::createData(frts::SharedManagerPtr)
{
    return false;
}

std::string frts::ModelFactoryImpl::getName() const
{
    return "frts::ModelFactory";
}

std::vector<std::string> frts::ModelFactoryImpl::getSupportedConfig()
{
    return {};
}

int frts::ModelFactoryImpl::getVersion() const
{
    return 1;
}

bool frts::ModelFactoryImpl::init(frts::SharedManagerPtr)
{
    return false;
}

frts::PointPtr frts::ModelFactoryImpl::makePoint(Point::value x, Point::value y, Point::value z)
{
    return frts::makePoint(x, y, z);
}

void frts::ModelFactoryImpl::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

void frts::ModelFactoryImpl::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
}

void frts::ModelFactoryImpl::validateModules(frts::SharedManagerPtr)
{
    // Everything is ok.
}
