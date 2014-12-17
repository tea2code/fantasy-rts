#include "VanillaDemoTickable.h"

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
    auto entity = modelFactory->makeEntity(shared->makeId(id), shared);
    regionManager->setPos(entity, pos, shared);
    highlights.push_back(entity);
}

void frts::VanillaDemoTickable::checkRequiredData(SharedManagerPtr shared)
{
    validateDataValue(getName(), Sdl2Ids::graphicData(), 1, shared);
}

bool frts::VanillaDemoTickable::init(frts::SharedManagerPtr shared)
{
    shared->getLog()->debug(getName(), "Demo loaded");
    return false;
}

void frts::VanillaDemoTickable::resetHighlights(RegionManagerPtr regionManager, SharedManagerPtr shared)
{
    for (auto& entity : highlights)
    {
        regionManager->removeEntity(entity, shared);
    }
    highlights.clear();
}

void frts::VanillaDemoTickable::tick(frts::SharedManagerPtr shared)
{
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    if (shared->getFrame()->getNumber() == 0)
    {
        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

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
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto pathFinder = mf->getPathFinder();
    auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), player);

    auto leftTop = mf->makePoint(5, 5, 0);
    auto rightTop = mf->makePoint(95, 5, 0);
    auto leftBottom = mf->makePoint(5, 95, 0);
    auto rightBottom = mf->makePoint(95, 95, 0);
    for (int i = 0; i < 100; ++i)
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
    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
    validateTickable(getName(), "frts::SDL2Renderer", 1, shared);
}
