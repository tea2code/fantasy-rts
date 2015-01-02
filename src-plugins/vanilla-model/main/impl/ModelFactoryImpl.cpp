#include "ModelFactoryImpl.h"

#include "RegionManagerImpl.h"

#include <entity/ComponentIds.h>
#include <entity/impl/BlockedByBuilder.h>
#include <entity/impl/BlockingBuilder.h>
#include <entity/impl/DropBuilder.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/HasResourceBuilder.h>
#include <entity/impl/IsResourceBuilder.h>
#include <entity/impl/MovableBuilder.h>
#include <entity/impl/SortOrderBuilder.h>
#include <entity/impl/TeleportBuilder.h>
#include <event/ModelEventIds.h>
#include <event/impl/EntityEventValueBuilder.h>
#include <event/impl/PointEventValueBuilder.h>
#include <main/ModelError.h>
#include <main/ModelIds.h>
#include <region/impl/PointImpl.h>
#include <regiongenerator/impl/RegionGeneratorImpl.h>
#include <regiongenerator/impl/BmpMapParser.h>
#include <regiongenerator/impl/TextMapParser.h>
#include <regiongenerator/RegionGeneratorIds.h>
#include <region/impl/RegionImpl.h>
#include <pathfinding/impl/AStar.h>
#include <pathfinding/impl/ManhattanDistance.h>
#include <resource/impl/LockableHasResourceManager.h>
#include <resource/impl/LockableIsResourceManager.h>

#include <frts/configuration>
#include <frts/shared>
#include <frts/vanillaevent>

#include <boost/format.hpp>

#include <memory>


frts::ModelFactoryImpl::ModelFactoryImpl()
{
}

void frts::ModelFactoryImpl::checkRequiredData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), ModelIds::modelData(), 2, shared);
    validateDataValue(getName(), MainIds::mainData(), 2, shared);
}

bool frts::ModelFactoryImpl::createData(frts::SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // Create model data.
    auto modelData = makeModelData();
    auto modelDataId = shared->makeId(ModelIds::modelData());
    shared->setDataValue(modelDataId, modelData);

    return false;
}

frts::DistanceAlgorithmPtr frts::ModelFactoryImpl::getDistanceAlgorithm() const
{
    return distanceAlgorithm;
}

frts::MapParserPtr frts::ModelFactoryImpl::getMapParser(IdPtr id) const
{
    assert(id != nullptr);

    auto it = mapParsers.find(id);
    if(it != mapParsers.end())
    {
        return it->second;
    }
    else
    {
        auto msg = boost::format(unknownMapParserError) % id->toString() % getName();
        throw UnknownMapParserError(msg.str());
    }
}

std::string frts::ModelFactoryImpl::getName() const
{
    return ModelIds::modelFactory();
}

frts::PathFinderPtr frts::ModelFactoryImpl::getPathFinder() const
{
    return pathFinder;
}

std::vector<std::string> frts::ModelFactoryImpl::getSupportedConfig()
{
    std::vector<std::string> result = {entitiesConfigKey, modelDataKey};

    // Map parser.
    for (auto& mapParser : mapParsers)
    {
        result.push_back(mapParser.second->getSupportedConfig());
    }

    // Region generator.
    result.push_back(regionGenerator->getSupportedConfig());

    return result;
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
    assert(shared != nullptr);

    // Wait one execution to allow other modules to override implementations
    // (for example replacing the original region with another using setRegion()).
    if (firstInit)
    {
        firstInit = false;
        return true;
    }

    // Components:
    shared->getLog()->info(getName(), "ModelFactory->init(): Components.");

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

    // Movable.
    auto movableId = shared->makeId(ComponentIds::movable());
    componentBuilder = makeMovableBuilder();
    registerComponentBuilder(movableId, componentBuilder);

    // SortOrder.
    auto sortOrderId = shared->makeId(ComponentIds::sortOrder());
    componentBuilder = makeSortOrderBuilder();
    registerComponentBuilder(sortOrderId, componentBuilder);

    // Teleport.
    auto teleportId = shared->makeId(ComponentIds::teleport());
    componentBuilder = makeTeleportBuilder();
    registerComponentBuilder(teleportId, componentBuilder);

    // Map parser.
    shared->getLog()->info(getName(), "ModelFactory->init(): MapParser.");
    for (auto& mapParser : mapParsers)
    {
        mapParser.second->init(shared);
    }

    // Distance algorithm:
    shared->getLog()->info(getName(), "ModelFactory->init(): DistanceAlgorithm.");
    if (distanceAlgorithm == nullptr)
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Default distance algorithm.");

        // Use a scale slightly greater 1.0 to tie break between similar costing positions.
        distanceAlgorithm = makeManhattanDistance(1.01);
    }
    else
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Custom distance algorithm.");
    }

    // Path finder:
    shared->getLog()->info(getName(), "ModelFactory->init(): PathFinder.");
    if (pathFinder == nullptr)
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Default path finder.");
        pathFinder = makeAStar(distanceAlgorithm, teleportId);
    }
    else
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Custom path finder.");
    }

    // Region generator.
    shared->getLog()->info(getName(), "ModelFactory->init(): RegionGenerator.");
    assert(regionGenerator != nullptr);
    regionGenerator->init(shared);

    // Region Manager:
    shared->getLog()->info(getName(), "ModelFactory->init(): RegionManager.");
    auto modelData = getDataValue<ModelData>(shared, ModelIds::modelData());
    auto hasResourceTyp = shared->makeId(ComponentIds::hasResource());
    auto isResourceType = shared->makeId(ComponentIds::isResource());

    if (region == nullptr)
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Default region.");
        region = makeRegion(modelData->getMapSizeX(), modelData->getMapSizeY(),
                            regionGenerator);
    }
    else
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Custom region.");
    }

    if (resourceEntityManager == nullptr)
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Default resource entity manager.");
        resourceEntityManager = makeLockableHasResourceManager(hasResourceTyp,
                                                               region,
                                                               distanceAlgorithm);
    }
    else
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Custom resource entity manager.");
    }

    if (resourceManager == nullptr)
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Default resource manager.");
        resourceManager = makeLockableIsResourceManager(isResourceType,
                                                        region,
                                                        distanceAlgorithm);
    }
    else
    {
        shared->getLog()->info(getName(), "ModelFactory->init(): Custom resource manager.");
    }

    // Check if everything is set.
    assert(distanceAlgorithm != nullptr);
    assert(pathFinder != nullptr);
    assert(region != nullptr);
    assert(resourceEntityManager != nullptr);
    assert(resourceManager != nullptr);

    // Add region manager to data values. This should happen in createData() but
    // is currently not possible.
    auto regionManager = makeRegionManager(region, resourceManager, resourceEntityManager,
                                           hasResourceTyp, isResourceType);
    auto regionManagerId = shared->makeId(ModelIds::regionManager());
    shared->setDataValue(regionManagerId, regionManager);

    // Log region manager because this is not possible in the kernel.
    auto msg = boost::format(R"(Data value "%1%" (Version %4%) of type "%2%" (Version %3%) loaded.)")
            % regionManager->getName() % regionManager->getTypeName()
            % regionManager->getTypeVersion() % regionManager->getVersion();
    shared->getLog()->warning(getName(), msg.str());

    // Event values.
#ifndef UNIT_TEST
    shared->getLog()->info(getName(), "ModelFactory->init(): EventValue.");
    auto eventManager = getUtility<EventManager>(shared, EventIds::eventManager());

    auto eventValueType = shared->makeId(ModelEventIds::entityEventValue());
    auto eventValueBuilder = makeEntityEventValueBuilder(eventValueType);
    eventManager->registerEventValueBuilder(eventValueType, eventValueBuilder);

    eventValueType = shared->makeId(ModelEventIds::pointEventValue());
    eventValueBuilder = makePointEventValueBuilder(eventValueType);
    eventManager->registerEventValueBuilder(eventValueType, eventValueBuilder);
#endif

    // Finished.
    shared->getLog()->info(getName(), "ModelFactory->init(): Finished.");
    isInit = true;
    return false;
}

bool frts::ModelFactoryImpl::isInitialized() const
{
    return isInit;
}

bool frts::ModelFactoryImpl::isPreInitialized() const
{
    return isPreInit;
}

frts::ComponentPtr frts::ModelFactoryImpl::makeComponent(IdPtr builderId, SharedManagerPtr shared)
{
    assert(builderId != nullptr);
    assert(shared != nullptr);

    auto it = componentBuilders.find(builderId);
    if(it != componentBuilders.end())
    {
        return it->second->build(shared);
    }
    else
    {
        auto msg = boost::format(unknownComponentBuilderError) % builderId->toString() % getName();
        throw UnknownComponentBuilderError(msg.str());
    }
}

frts::ComponentPtr frts::ModelFactoryImpl::makeComponent(IdPtr builderId, ConfigNodePtr node, SharedManagerPtr shared)
{
    assert(builderId != nullptr);
    assert(node != nullptr);
    assert(shared != nullptr);

    auto it = componentBuilders.find(builderId);
    if(it != componentBuilders.end())
    {
        return it->second->build(shared, node);
    }
    else
    {
        auto msg = boost::format(unknownComponentBuilderError) % builderId->toString() % getName();
        throw UnknownComponentBuilderError(msg.str());
    }
}

frts::EntityPtr frts::ModelFactoryImpl::makeEntity()
{
    return frts::makeEntity();
}

frts::EntityPtr frts::ModelFactoryImpl::makeEntity(IdPtr id, SharedManagerPtr shared)
{
    assert(id != nullptr);
    assert(shared != nullptr);

    try
    {
        auto entity = makeEntity();
        for (auto& componentNodes : entityConfig.at(id))
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
        auto msg = boost::format(R"(%2%: Entity "%1%" has no configuration.)") % id->toString() % getName();
        throw UnknownEntityError(msg.str());
    }
}

frts::PointPtr frts::ModelFactoryImpl::makePoint(Point::value x, Point::value y, Point::value z)
{
    return frts::makePoint(x, y, z);
}

void frts::ModelFactoryImpl::parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared)
{
    assert(node != nullptr);
    assert(shared != nullptr);

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
    else if (key == modelDataKey)
    {
        auto modelData = getDataValue<ModelData>(shared, ModelIds::modelData());

        modelData->setMapSizeX(node->getInteger("width", modelData->getMapSizeX()));
        modelData->setMapSizeY(node->getInteger("height", modelData->getMapSizeY()));
        modelData->setPrecalculateDown(node->getInteger("precalculate_down", modelData->getPrecalculateDown()));
        modelData->setPrecalculateUp(node->getInteger("precalculate_up", modelData->getPrecalculateUp()));
        modelData->setSurfaceZLevel(node->getInteger("surface_level", modelData->getSurfaceZLevel()));
    }
    else if (key == regionGenerator->getSupportedConfig())
    {
        regionGenerator->parseConfig(node, shared);
    }
    else
    {
        // Map parser.
        for (auto& mapParser : mapParsers)
        {
            if (mapParser.second->getSupportedConfig() == key)
            {
                mapParser.second->parseConfig(node, shared);
            }
        }
    }
}

bool frts::ModelFactoryImpl::preInit(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto blockingId = shared->makeId(ComponentIds::blocking());
    auto sortOrderId = shared->makeId(ComponentIds::sortOrder());
    auto teleportId = shared->makeId(ComponentIds::teleport());

    // Map parser:
    // BMP.
    auto bmpMapParserId = shared->makeId(RegionGeneratorIds::bmpMapParser());
    registerMapParser(bmpMapParserId, makeBmpMapParser(blockingId, sortOrderId, teleportId));

    // Text.
    // TODO Implement text map parser.
//    auto textMapParserId = shared->makeId(RegionGeneratorIds::textMapParser());
//    registerMapParser(textMapParserId, makeTextMapParser());

    // Region generator:
    if (regionGenerator == nullptr)
    {
        regionGenerator = makeRegionGenerator(blockingId, sortOrderId);
    }

    isPreInit = true;
    return false;
}

void frts::ModelFactoryImpl::setDistanceAlgorithm(DistanceAlgorithmPtr distanceAlgorithm)
{
    this->distanceAlgorithm = distanceAlgorithm;
}

void frts::ModelFactoryImpl::setPathFinder(PathFinderPtr pathFinder)
{
    this->pathFinder = pathFinder;
}

void frts::ModelFactoryImpl::registerComponentBuilder(IdPtr builderId, ComponentBuilderPtr builder)
{
    assert(builderId != nullptr);
    assert(builder != nullptr);

    componentBuilders[builderId] = builder;
}

void frts::ModelFactoryImpl::registerMapParser(IdPtr id, MapParserPtr mapParser)
{
    assert(id != nullptr);
    assert(mapParser != nullptr);

    mapParsers[id] = mapParser;
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
    assert(shared != nullptr);

    auto modelData = getDataValue<ModelData>(shared, ModelIds::modelData());
    if (modelData->getMapSizeX() <= 0)
    {
        auto msg = boost::format(R"(%1%: Region width must be greater than zero.)") % getName();
        throw DataViolation(msg.str());
    }
    if (modelData->getMapSizeY() <= 0)
    {
        auto msg = boost::format(R"(%1%: Region height must be greater than zero.)") % getName();
        throw DataViolation(msg.str());
    }

    // Map parser.
    for (auto& mapParser : mapParsers)
    {
        mapParser.second->validateData(shared);
    }

    // Region generator.
    regionGenerator->validateData(shared);
}

void frts::ModelFactoryImpl::validateModules(SharedManagerPtr shared)
{
    validateUtility(getName(), EventIds::eventManager(), 1, shared);
}
