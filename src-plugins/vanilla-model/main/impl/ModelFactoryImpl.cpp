#include "ModelFactoryImpl.h"

#include "RegionManagerImpl.h"

#include <entity/ComponentIds.h>
#include <entity/impl/BlockedByBuilder.h>
#include <entity/impl/BlockingBuilder.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceBuilder.h>
#include <entity/impl/IsResourceBuilder.h>
#include <entity/impl/SortOrderBuilder.h>
#include <main/ModelError.h>
#include <region/impl/PointImpl.h>

#include <frts/shared>

#include <boost/format.hpp>

#include <memory>


frts::ModelFactoryImpl::ModelFactoryImpl()
{
}

bool frts::ModelFactoryImpl::createData(frts::SharedManagerPtr shared)
{
    // Add region manager to data values.
    RegionManagerPtr regionManager = makeRegionManager();
    IdPtr id = shared->makeId(regionManager->identifier);
    shared->setDataValue(id, regionManager);

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

bool frts::ModelFactoryImpl::init(frts::SharedManagerPtr shared)
{
    /**
     * @todo The implementation should wait the first call of init() (return true)
     *       so that other plugins may change the default implementations. Only in
     *       the second call the initialization is executed. For example should
     *       the pathfinding plugin being able to set it's own distance algorithm
     *       instead of the default implementation of Vanilla Model.
     */

    // BlockedBy.
    IdPtr id = shared->makeId(ComponentIds::blockedBy());
    ComponentBuilderPtr componentBuilder = makeBlockedByBuilder();
    registerComponentBuilder(id, componentBuilder);

    // Blocking.
    id = shared->makeId(ComponentIds::blocking());
    componentBuilder = makeBlockingBuilder();
    registerComponentBuilder(id, componentBuilder);

    // HasResource.
    id = shared->makeId(ComponentIds::hasResource());
    componentBuilder = makeHasResourceBuilder();
    registerComponentBuilder(id, componentBuilder);

    // IsResource.
    id = shared->makeId(ComponentIds::isResource());
    componentBuilder = makeIsResourceBuilder();
    registerComponentBuilder(id, componentBuilder);

    // SortOrder.
    id = shared->makeId(ComponentIds::sortOrder());
    componentBuilder = makeSortOrderBuilder();
    registerComponentBuilder(id, componentBuilder);

    return false;
}

frts::ComponentPtr frts::ModelFactoryImpl::makeComponent(IdPtr builderId, SharedManagerPtr shared)
{
    auto it = componentBuilders.find(builderId);
    if(it != componentBuilders.end())
    {
        return it->second->build(shared);
    }
    else
    {
        auto msg = boost::format(R"(No component builder is registered for ID "%1%".)") % builderId->toString();
        throw UnknownBuilderError(msg.str());
    }
}

frts::EntityPtr frts::ModelFactoryImpl::makeEntity()
{
    return frts::makeEntity();
}

frts::PointPtr frts::ModelFactoryImpl::makePoint(Point::value x, Point::value y, Point::value z)
{
    return frts::makePoint(x, y, z);
}

void frts::ModelFactoryImpl::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

void frts::ModelFactoryImpl::registerComponentBuilder(IdPtr builderId, ComponentBuilderPtr builder)
{
    componentBuilders[builderId] = builder;
}

void frts::ModelFactoryImpl::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
}

void frts::ModelFactoryImpl::validateModules(frts::SharedManagerPtr)
{
    // Everything is ok.
}
