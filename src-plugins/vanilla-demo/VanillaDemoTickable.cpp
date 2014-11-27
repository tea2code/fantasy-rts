#include "VanillaDemoTickable.h"

#include "DemoRegionGenerator.h"

#include <frts/shared>
#include <frts/vanillacommand>
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

bool frts::VanillaDemoTickable::init(frts::SharedManagerPtr shared)
{
    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    Point::value surfaceZLevel = 0;
    auto blockingType = shared->makeId(ComponentIds::blocking());
    auto sortOrderType = shared->makeId(ComponentIds::sortOrder());
    auto regionConfig = getDataValue<RegionConfig>(shared, ModelIds::regionConfig());
    auto regionGenerator = makeDemoRegionGenerator(blockingType, sortOrderType,
                                                   regionConfig->getMapSizeX(), regionConfig->getMapSizeY(),
                                                   surfaceZLevel);
    modelFactory->setRegionGenerator(regionGenerator);

    shared->getLog()->debug(getName(), "Demo loaded");
    return false;
}

void frts::VanillaDemoTickable::resetHighlights(RegionManagerPtr regionManager, SharedManagerPtr shared)
{
    for (auto entity : highlights)
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
        auto rc = getDataValue<RegionConfig>(shared, ModelIds::regionConfig());

        // Add dwarf at start position.
        player = mf->makeEntity(shared->makeId("entity.dwarf"), shared);
        rm->setPos(player, mf->makePoint(0, 0, 0), shared);

        // Initialize position of cursor.
        lastCursorPos = rm->getPos(gd->getCursor(), shared);

        // Pregenerate map.
        for (auto x = 0; x < rc->getMapSizeX(); ++x)
        {
            for (auto y = 0; y < rc->getMapSizeY(); ++y)
            {
                auto pos = mf->makePoint(x, y, gd->getZLevel());
                rm->getBlock(pos, shared);
            }
        }
    }

    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    if (shared->getFrame()->getNumber() % 100 == 0 && lastCursorPos != cursorPos)
    {
        lastCursorPos = cursorPos;

        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        auto pathFinder = mf->getPathFinder();
        auto start = rm->getPos(player, shared);
        auto blockedBy = getComponent<BlockedBy>(shared->makeId(ComponentIds::blockedBy()), player);
        auto path = pathFinder->findPath(start, cursorPos, blockedBy, shared);
        if (!path.empty())
        {
            auto movable = getComponent<Movable>(shared->makeId(ComponentIds::movable()), player);
            movable->setPath(path);

            resetHighlights(rm, shared);
            auto lastCosts = pathFinder->getLastCosts();
            double highestCost = 0.0;
            for (auto it : lastCosts)
            {
                highestCost = std::max(highestCost, it.second);
            }
            for (auto it : lastCosts)
            {
                std::string id = "entity.highlight.red";
                if (it.second > highestCost * 0.75)
                {
                    id = "entity.highlight.green";
                }
                else if (it.second > highestCost * 0.5)
                {
                    id = "entity.highlight.yellow";
                }
                else if (it.second > highestCost * 0.25)
                {
                    id = "entity.highlight.orange";
                }
                addHighlight(mf, rm, shared, it.first, id);
            }
            for (auto pos : path)
            {
                addHighlight(mf, rm, shared, pos, "entity.dot");
            }
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
}

void frts::VanillaDemoTickable::validateModules(frts::SharedManagerPtr shared)
{
    try
    {
        UtilityPtr module = getUtility<Utility>(shared, CommandIds::commandFactory());
        if (module->getVersion() != 1)
        {
            throw ModuleViolation("Utility CommandFactory has the wrong version.");
        }
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility CommandFactory not found.");
    }

    try
    {
        getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility ModelFactory not found.");
    }
}
