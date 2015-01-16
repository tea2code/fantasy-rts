#include "VanillaDemoTickable.h"

#include "DemoRegionGenerator.h"
#include <frts/shared>
#include <frts/vanillajob>
#include <frts/vanillamodel>
#include <frts/vanillasdl2graphic>

#include <algorithm>


frts::VanillaDemoTickable::VanillaDemoTickable()
    : BaseTickable("frts::VanillaDemo", 1, "frts::VanillaDemo", 1)
{
}

void frts::VanillaDemoTickable::addHighlight(const ModelFactoryPtr& modelFactory, const RegionManagerPtr& regionManager,
                                             const SharedManagerPtr& shared, const PointPtr& pos, const std::string& id)
{
    assert(modelFactory != nullptr);
    assert(regionManager != nullptr);
    assert(shared != nullptr);
    assert(pos != nullptr);

    auto entity = modelFactory->makeEntity(shared->makeId(id), shared);
    regionManager->setPos(entity, pos, shared);
    highlights.push_back(entity);
}

void frts::VanillaDemoTickable::checkRequiredData(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), Sdl2Ids::graphicData(), 4, shared);
}

bool frts::VanillaDemoTickable::init(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    #ifdef A_STAR_BENCHMARK
    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto blockingType = shared->makeId(ComponentIds::blocking());
    auto sortOrderType = shared->makeId(ComponentIds::sortOrder());
    auto modelData = getDataValue<ModelData>(shared, ModelIds::modelData());
    auto regionGenerator = makeDemoRegionGenerator(blockingType, sortOrderType,
                                                   modelData->getMapSizeX(), modelData->getMapSizeY(),
                                                   0);
    modelFactory->setRegionGenerator(regionGenerator);
    #endif

    auto em = getUtility<EventManager>(shared, EventIds::eventManager());
    em->subscribe(shared_from_this(), shared->makeId(JobIds::jobCanceledEvent()));
    em->subscribe(shared_from_this(), shared->makeId(JobIds::jobFinishedEvent()));
    em->subscribe(shared_from_this(), shared->makeId(JobIds::jobStoppedEvent()));

    return BaseTickable::init(shared);
}

void frts::VanillaDemoTickable::resetHighlights(const RegionManagerPtr& regionManager, const SharedManagerPtr& shared)
{
    assert(regionManager != nullptr);
    assert(shared != nullptr);

    for (auto& entity : highlights)
    {
        regionManager->removeEntity(entity, shared);
    }
    highlights.clear();
}

void frts::VanillaDemoTickable::notify(const EventPtr& event, const SharedManagerPtr& shared)
{
    assert(event != nullptr);
    assert(shared != nullptr);

    if (event->getType() == shared->makeId(JobIds::jobCanceledEvent()) ||
        event->getType() == shared->makeId(JobIds::jobFinishedEvent()) ||
        event->getType() == shared->makeId(JobIds::jobStoppedEvent()))
    {
        auto entityValue = getEventValue<EntityEventValue>(event, shared->makeId(JobIds::entityEventValue()));
        auto it = std::find(working.begin(), working.end(), entityValue->getValue());
        if (it != working.end())
        {
            lazy.push_back(*it);
            working.erase(it);
        }
        else
        {
            shared->getLog()->warning(getName(), "Working entity which is not in working list.");
        }
    }
}

void frts::VanillaDemoTickable::tick(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    if (shared->getFrame()->getNumber() == 0)
    {
        // Add dwarves.

#ifdef A_STAR_BENCHMARK
        const unsigned int numEntities = 1;
#else
        const unsigned int numEntities = 10;
#endif
        const auto entityId = shared->makeId("entity.dwarf");

        auto blockedById = shared->makeId(ComponentIds::blockedBy());
        auto md = getDataValue<ModelData>(shared, ModelIds::modelData());
        for (unsigned int i = 0; i < numEntities; ++i)
        {
            auto entity = mf->makeEntity(entityId, shared);
            auto blockedBy = getComponent<BlockedBy>(blockedById, entity);
            auto pos = rm->findFreeRandomPos({md->getSurfaceZLevel()}, blockedBy, shared);
            if (pos != nullptr)
            {
                rm->setPos(entity, pos, shared);
                lazy.push_back(entity);
            }
            else
            {
                shared->getLog()->warning(getName(), "Couldn't find a free position for entity.");
            }
        }

        return;
    }

#ifdef A_STAR_BENCHMARK
    const int numIterations = 1000;

    // Pregenerate map.
    auto md = getDataValue<ModelData>(shared, ModelIds::modelData());
    for (Point::value x = 0; x < md->getMapSizeX(); ++x)
    {
        for (Point::value y = 0; y < md->getMapSizeY(); ++y)
        {
            for (Point::value z = 0; z < 20; ++z)
            {
                auto pos = mf->makePoint(x, y, 0);
                rm->getBlock(pos, shared);
            }
        }
    }

    auto pathFinder = mf->getPathFinder();
    auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), lazy.at(0));

    auto leftTop = mf->makePoint(5, 5, 0);
    auto rightTop = mf->makePoint(95, 5, 0);
    auto leftBottom = mf->makePoint(5, 95, 0);
    auto rightBottom = mf->makePoint(95, 95, 0);
    for (int i = 0; i < numIterations; ++i)
    {
        pathFinder->findPath(leftTop, rightBottom, blockedBy, shared);
        pathFinder->findPath(rightBottom, rightTop, blockedBy, shared);
        pathFinder->findPath(rightTop, leftBottom, blockedBy, shared);
        pathFinder->findPath(leftBottom, leftTop, blockedBy, shared);
    }
    shared->setQuitApplication(true);
#else
    // Temporary ai replacement.
    if (shared->getFrame()->getNumber() % 50 == 0)
    {
        auto jm = getUtility<JobManager>(shared, JobIds::jobManager());
        for (auto it = lazy.begin(); it != lazy.end();)
        {
            bool isWorking = jm->employEntity(*it, shared);
            if (isWorking)
            {
                working.push_back(*it);
                it = lazy.erase(it);

                shared->getLog()->debug(getName(), "Found work.");
            }
            else
            {
                ++it;
            }
        }
    }
#endif
}

void frts::VanillaDemoTickable::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 2, shared);
    validateTickable(getName(), Sdl2Ids::sdl2Renderer(), 1, shared);
    validateUtility(getName(), EventIds::eventManager(), 1, shared);
    validateUtility(getName(), JobIds::jobManager(), 3, shared);
}
