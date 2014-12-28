#include "VanillaDemoTickable.h"

#include "DemoRegionGenerator.h"
#include <frts/shared>
#include <frts/vanillamodel>
#include <frts/vanillasdl2graphic>

#include <algorithm>


frts::VanillaDemoTickable::VanillaDemoTickable()
    : BaseTickable("frts::VanillaDemo", 1, "frts::VanillaDemo", 1)
{
}

void frts::VanillaDemoTickable::addHighlight(ModelFactoryPtr modelFactory, RegionManagerPtr regionManager,
                                             SharedManagerPtr shared, PointPtr pos, const std::string& id)
{
    assert(modelFactory != nullptr);
    assert(regionManager != nullptr);
    assert(shared != nullptr);
    assert(pos != nullptr);

    auto entity = modelFactory->makeEntity(shared->makeId(id), shared);
    regionManager->setPos(entity, pos, shared);
    highlights.push_back(entity);
}

void frts::VanillaDemoTickable::checkRequiredData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), Sdl2Ids::graphicData(), 2, shared);
}

bool frts::VanillaDemoTickable::init(frts::SharedManagerPtr shared)
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

    shared->getLog()->debug(getName(), "Demo loaded");
    isInit = true;
    return false;
}

void frts::VanillaDemoTickable::resetHighlights(RegionManagerPtr regionManager, SharedManagerPtr shared)
{
    assert(regionManager != nullptr);
    assert(shared != nullptr);

    for (auto& entity : highlights)
    {
        regionManager->removeEntity(entity, shared);
    }
    highlights.clear();
}

void frts::VanillaDemoTickable::tick(frts::SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    if (shared->getFrame()->getNumber() == 0)
    {
        // Add dwarf at start position.
        player = mf->makeEntity(shared->makeId("entity.dwarf"), shared);
        auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), player);
        auto pos = rm->findFreeRandomPos({0}, blockedBy, shared);
        if (pos != nullptr)
        {
            rm->setPos(player, pos, shared);
        }

        // Initialize position of cursor.
        lastCursorPos = rm->getPos(gd->getCursor(), shared);

        return;
    }

    #ifdef A_STAR_BENCHMARK
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
    auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), player);

    auto leftTop = mf->makePoint(5, 5, 0);
    auto rightTop = mf->makePoint(95, 5, 0);
    auto leftBottom = mf->makePoint(5, 95, 0);
    auto rightBottom = mf->makePoint(95, 95, 0);
    for (int i = 0; i < 300; ++i)
    {
        pathFinder->findPath(leftTop, rightBottom, blockedBy, shared);
        pathFinder->findPath(rightBottom, rightTop, blockedBy, shared);
        pathFinder->findPath(rightTop, leftBottom, blockedBy, shared);
        pathFinder->findPath(leftBottom, leftTop, blockedBy, shared);
    }
    shared->setQuitApplication(true);
    #else
    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    if (shared->getFrame()->getNumber() % 50 == 0 && lastCursorPos != cursorPos)
    {
        lastCursorPos = cursorPos;

        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        auto pathFinder = mf->getPathFinder();
        auto start = rm->getPos(player, shared);
        if (start == nullptr)
        {
            return;
        }
        auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), player);
        auto path = pathFinder->findPath(start, cursorPos, blockedBy, shared);
        if (path->pathExists())
        {
            auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), player);
            movable->setPath(path);

//            resetHighlights(rm, shared);
//            auto lastCosts = pathFinder->getLastCosts();
//            double highestCost = 0.0;
//            for (auto it : lastCosts)
//            {
//                highestCost = std::max(highestCost, it.second);
//            }
//            for (auto it : lastCosts)
//            {
//                std::string id = "entity.highlight.red";
//                if (it.second > highestCost * 0.75)
//                {
//                    id = "entity.highlight.green";
//                }
//                else if (it.second > highestCost * 0.5)
//                {
//                    id = "entity.highlight.yellow";
//                }
//                else if (it.second > highestCost * 0.25)
//                {
//                    id = "entity.highlight.orange";
//                }
//                addHighlight(mf, rm, shared, it.first, id);
//            }
//            for (auto pos : path)
//            {
//                addHighlight(mf, rm, shared, pos, "entity.dot");
//            }
        }
    }

    if (shared->getFrame()->getNumber() % 5 == 0)
    {
        auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), player);
        auto nextPos = movable->getNextPathPos();
        if (nextPos != nullptr)
        {
            rm->removeEntity(player, shared);
            rm->setPos(player, nextPos, shared);
        }
    }
    #endif
}

void frts::VanillaDemoTickable::validateModules(frts::SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
    validateTickable(getName(), "frts::SDL2Renderer", 1, shared);
}
