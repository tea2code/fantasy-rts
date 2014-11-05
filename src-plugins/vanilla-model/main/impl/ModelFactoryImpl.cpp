#include "ModelFactoryImpl.h"

#include "RegionConfigImpl.h"
#include "RegionManagerImpl.h"

#include <entity/ComponentIds.h>
#include <entity/impl/BlockedByBuilder.h>
#include <entity/impl/BlockingBuilder.h>
#include <entity/impl/DropBuilder.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceBuilder.h>
#include <entity/impl/IsResourceBuilder.h>
#include <entity/impl/SortOrderBuilder.h>
#include <main/ModelError.h>
#include <main/ModelIds.h>
#include <region/impl/PointImpl.h>
#include <region/impl/RegionGeneratorImpl.h>
#include <region/impl/RegionImpl.h>
#include <resource/impl/DistanceAlgorithmImpl.h>
#include <resource/impl/LockableHasResourceManager.h>
#include <resource/impl/LockableIsResourceManager.h>

#include <frts/configuration>
#include <frts/shared>

#include <boost/format.hpp>

#include <memory>


frts::ModelFactoryImpl::ModelFactoryImpl()
{
}

bool frts::ModelFactoryImpl::createData(frts::SharedManagerPtr shared)
{
    // Create region config data.
    auto regionConfig = makeRegionConfig();
    auto regionConfigId = shared->makeId(ModelIds::regionConfig());
    shared->setDataValue(regionConfigId, regionConfig);

    return false;
}

std::string frts::ModelFactoryImpl::getName() const
{
    return ModelIds::modelFactory();
}

std::vector<std::string> frts::ModelFactoryImpl::getSupportedConfig()
{
    return {entitiesConfigKey, regionConfigKey};
}

std::string frts::ModelFactoryImpl::getTypeName() const
{
    return getName();
}

int frts::ModelFactoryImpl::getTypeVersion() const
{
    return 1;
}

int frts::ModelFactoryImpl::getVersion() const
{
    return 1;
}

bool frts::ModelFactoryImpl::init(SharedManagerPtr shared)
{
    if (firstInit)
    {
        firstInit = false;
        return true;
    }

    // Components:
    // BlockedBy.
    auto blockedById = shared->makeId(ComponentIds::blockedBy());
    auto componentBuilder = makeBlockedByBuilder();
    registerComponentBuilder(blockedById, componentBuilder);

    // Blocking.
    auto blockingId = shared->makeId(ComponentIds::blocking());
    componentBuilder = makeBlockingBuilder();
    registerComponentBuilder(blockingId, componentBuilder);

    // Drop.
    auto dropId = shared->makeId(ComponentIds::drop());
    componentBuilder = makeDropBuilder();
    registerComponentBuilder(dropId, componentBuilder);

    // HasResource.
    auto hasResourceId = shared->makeId(ComponentIds::hasResource());
    componentBuilder = makeHasResourceBuilder();
    registerComponentBuilder(hasResourceId, componentBuilder);

    // IsResource.
    auto isResourceId = shared->makeId(ComponentIds::isResource());
    componentBuilder = makeIsResourceBuilder();
    registerComponentBuilder(isResourceId, componentBuilder);

    // SortOrder.
    auto sortOrderId = shared->makeId(ComponentIds::sortOrder());
    componentBuilder = makeSortOrderBuilder();
    registerComponentBuilder(sortOrderId, componentBuilder);

    // Region Manager:
    auto regionConfig = getRegionConfig(shared);
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
    auto regionManager = makeRegionManager(region, resourceManager, resourceEntityManager,
                                           hasResourceType, isResourceType);
    auto regionManagerId = shared->makeId(ModelIds::regionManager());
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
        auto msg = boost::format(unknownComponentBuilderError) % builderId->toString();
        throw UnknownComponentBuilderError(msg.str());
    }
}

frts::ComponentPtr frts::ModelFactoryImpl::makeComponent(IdPtr builderId, ConfigNodePtr node, SharedManagerPtr shared)
{
    auto it = componentBuilders.find(builderId);
    if(it != componentBuilders.end())
    {
        return it->second->build(shared, node);
    }
    else
    {
        auto msg = boost::format(unknownComponentBuilderError) % builderId->toString();
        throw UnknownComponentBuilderError(msg.str());
    }
}

frts::EntityPtr frts::ModelFactoryImpl::makeEntity()
{
    return frts::makeEntity();
}

frts::EntityPtr frts::ModelFactoryImpl::makeEntity(IdPtr id, SharedManagerPtr shared)
{
    try
    {
        auto entity = makeEntity();
        for (auto componentNodes : entityConfig.at(id))
        {
            for (auto componentNode : *componentNodes)
            {
                auto componentId = shared->makeId(componentNode->getString("component"));
                auto component = makeComponent(componentId, componentNode, shared);
                entity->addComponent(component);
            }
        }
        return entity;
    }
    catch(const std::out_of_range&)
    {
        auto msg = boost::format(R"(Entity "%1%" has no configuration.)") % id->toString();
        throw UnknownEntityError(msg.str());
    }
}

frts::PointPtr frts::ModelFactoryImpl::makePoint(Point::value x, Point::value y, Point::value z)
{
    return frts::makePoint(x, y, z);
}

void frts::ModelFactoryImpl::parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared)
{
    if (key == entitiesConfigKey)
    {
        std::string namePrefix = "";
        if (node->has("namespace"))
        {
            namePrefix = node->getString("namespace");
            namePrefix += ".";
        }

        if (node->has("entities"))
        {
            auto entitiesNode = node->getNode("entities");
            for (auto entityNode : *entitiesNode)
            {
                auto id = shared->makeId(namePrefix + entityNode->getString("name"));
                auto componentsNode = entityNode->getNode("components");
                entityConfig[id].push_back(componentsNode);
            }
        }

        auto msg = boost::format(R"(Read %1% entity configurations.)") % entityConfig.size();
        shared->getLog()->debug(getName(), msg.str());
    }
    else if (key == regionConfigKey)
    {
        auto regionConfig = getRegionConfig(shared);
        regionConfig->setMapSizeX(node->getInteger("size_x"));
        regionConfig->setMapSizeY(node->getInteger("size_y"));
    }
}

bool frts::ModelFactoryImpl::preInit(SharedManagerPtr)
{
    return false;
}

frts::RegionConfigPtr frts::ModelFactoryImpl::getRegionConfig(SharedManagerPtr shared) const
{
    return getDataValue<RegionConfig>(shared, ModelIds::regionConfig());
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

void frts::ModelFactoryImpl::validateData(SharedManagerPtr shared)
{
    auto regionConfig = getRegionConfig(shared);
    if (regionConfig->getMapSizeX() <= 0)
    {
        throw DataViolation("Region:size_x must be greater than zero.");
    }
    if (regionConfig->getMapSizeY() <= 0)
    {
        throw DataViolation("Region:size_y must be greater than zero.");
    }
}

void frts::ModelFactoryImpl::validateModules(SharedManagerPtr)
{
    // Everything is ok.
}
