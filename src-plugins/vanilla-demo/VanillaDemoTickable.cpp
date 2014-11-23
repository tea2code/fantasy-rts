#include "VanillaDemoTickable.h"

#include "DemoRegionGenerator.h"

#include <frts/shared>
#include <frts/vanillacommand>
#include <frts/vanillamodel>
#include <frts/vanillasdl2graphic>


frts::VanillaDemoTickable::VanillaDemoTickable()
    : BaseTickable("frts::VanillaDemo", 1, "frts::VanillaDemo", 1)
{
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

void frts::VanillaDemoTickable::tick(frts::SharedManagerPtr shared)
{
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

    if (shared->getFrame()->getNumber() == 0)
    {
        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        player = mf->makeEntity(shared->makeId("entity.dwarf"), shared);
        rm->setPos(player, mf->makePoint(0, 0, 0), shared);

        lastCursorPos = rm->getPos(gd->getCursor(), shared);
    }

    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    if (lastCursorPos != cursorPos)
    {
        shared->getLog()->debug(getName(), "Cursor has moved.");
        lastCursorPos = cursorPos;
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
