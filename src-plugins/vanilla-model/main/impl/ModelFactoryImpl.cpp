#include "ModelFactoryImpl.h"

#include "RegionConfigImpl.h"
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
#include <region/impl/RegionGeneratorImpl.h>
#include <region/impl/RegionImpl.h>
#include <resource/impl/DistanceAlgorithmImpl.h>
#include <resource/impl/LockableHasResourceManager.h>
#include <resource/impl/LockableIsResourceManager.h>

#include <frts/shared>

#include <boost/format.hpp>

#include <memory>


frts::ModelFactoryImpl::ModelFactoryImpl()
{
}

bool frts::ModelFactoryImpl::createData(frts::SharedManagerPtr shared)
{
    // Create region config data.
    RegionConfigPtr regionConfig = makeRegionConfig();
    IdPtr regionConfigId = shared->makeId(regionConfig->identifier());
    shared->setDataValue(regionConfigId, regionConfig);

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
    // Components:
    // BlockedBy.
    IdPtr blockedById = shared->makeId(ComponentIds::blockedBy());
    ComponentBuilderPtr componentBuilder = makeBlockedByBuilder();
    registerComponentBuilder(blockedById, componentBuilder);

    // Blocking.
    IdPtr blockingId = shared->makeId(ComponentIds::blocking());
    componentBuilder = makeBlockingBuilder();
    registerComponentBuilder(blockingId, componentBuilder);

    // HasResource.
    IdPtr hasResourceId = shared->makeId(ComponentIds::hasResource());
    componentBuilder = makeHasResourceBuilder();
    registerComponentBuilder(hasResourceId, componentBuilder);

    // IsResource.
    IdPtr isResourceId = shared->makeId(ComponentIds::isResource());
    componentBuilder = makeIsResourceBuilder();
    registerComponentBuilder(isResourceId, componentBuilder);

    // SortOrder.
    IdPtr sortOrderId = shared->makeId(ComponentIds::sortOrder());
    componentBuilder = makeSortOrderBuilder();
    registerComponentBuilder(sortOrderId, componentBuilder);

    // Region Manager:
    // Initialize if not already done.
    IdPtr regionConfigId = shared->makeId(RegionConfigImpl::identifier());
    RegionConfigPtr regionConfig = std::static_pointer_cast<RegionConfig>(shared->getDataValue(regionConfigId));

    if (regionGenerator == nullptr)
    {
        regionGenerator = makeRegionGenerator(blockingId, sortOrderId,
                                              regionConfig->getMapSizeX(),
                                              regionConfig->getMapSizeY());
    }

    if (region == nullptr)
    {
        region = makeRegion(regionConfig->getMapSizeX(), regionConfig->getMapSizeY(),
                            regionGenerator);
    }

    if (distAlgo == nullptr)
    {
        distAlgo = makeDistanceAlgorithm();
    }

    if (hasResourceType == nullptr)
    {
        hasResourceType = shared->makeId(ComponentIds::hasResource());
    }

    if (isResourceType == nullptr)
    {
        isResourceType = shared->makeId(ComponentIds::isResource());
    }

    if (resourceEntityManager == nullptr)
    {
        resourceEntityManager = makeLockableHasResourceManager(hasResourceType,
                                                               region, distAlgo);
    }

    if (resourceManager == nullptr)
    {
        resourceManager = makeLockableIsResourceManager(isResourceType, region,
                                                        distAlgo);
    }

    // Add region manager to data values. This should happen in createData() but
    // is currently not possible.
    RegionManagerPtr regionManager = makeRegionManager(region, resourceManager,
                                                       resourceEntityManager,
                                                       hasResourceType, isResourceType);
    IdPtr regionManagerId = shared->makeId(regionManager->identifier());
    shared->setDataValue(regionManagerId, regionManager);

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

bool frts::ModelFactoryImpl::preInit(frts::SharedManagerPtr)
{
    return false;
}

void frts::ModelFactoryImpl::registerComponentBuilder(IdPtr builderId, ComponentBuilderPtr builder)
{
    componentBuilders[builderId] = builder;
}

void frts::ModelFactoryImpl::setDistanceAlgorithm(DistanceAlgorithmPtr distAlgo)
{
    this->distAlgo = distAlgo;
}

void frts::ModelFactoryImpl::setHasResourceType(IdPtr hasResourceType)
{
    this->hasResourceType = hasResourceType;
}

void frts::ModelFactoryImpl::setIsResourceType(IdPtr isResourceType)
{
    this->isResourceType = isResourceType;
}

void frts::ModelFactoryImpl::setRegion(RegionPtr region)
{
    this->region = region;
}

void frts::ModelFactoryImpl::setRegionGenerator(RegionGeneratorPtr regionGenerator)
{
    this->regionGenerator = regionGenerator;
}

void frts::ModelFactoryImpl::setResourceEntityManager(LockableResourceManagerPtr resourceEntityManager)
{
    this->resourceEntityManager = resourceEntityManager;
}

void frts::ModelFactoryImpl::setResourceManager(LockableResourceManagerPtr resourceManager)
{
    this->resourceManager = resourceManager;
}

void frts::ModelFactoryImpl::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
}

void frts::ModelFactoryImpl::validateModules(frts::SharedManagerPtr)
{
    // Everything is ok.
}
