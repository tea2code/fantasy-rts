#include "VanillaDemoTickable.h"

#include "DemoRegionGenerator.h"

#include <frts/shared>
#include <frts/vanillacommand>
#include <frts/vanillamodel>

#include <chrono>
#include <thread>


frts::VanillaDemoTickable::VanillaDemoTickable()
{
}

bool frts::VanillaDemoTickable::createData(frts::SharedManagerPtr)
{
    return false;
}

std::string frts::VanillaDemoTickable::getName() const
{
    return "frts::VanillaDemo";
}

std::vector<std::string> frts::VanillaDemoTickable::getSupportedConfig()
{
    return {};
}

std::string frts::VanillaDemoTickable::getTypeName() const
{
    return getName();
}

int frts::VanillaDemoTickable::getTypeVersion() const
{
    return 1;
}

int frts::VanillaDemoTickable::getVersion() const
{
    return 1;
}

bool frts::VanillaDemoTickable::init(frts::SharedManagerPtr shared)
{
    Point::value surfaceZLevel = 0;
    auto blockingType = shared->makeId(ComponentIds::blocking());
    auto sortOrderType = shared->makeId(ComponentIds::blocking());
    auto regionConfig = getDataValue<RegionConfig>(shared, ModelIds::regionConfig());
    auto regionGenerator = makeDemoRegionGenerator(blockingType, sortOrderType,
                                                   regionConfig->getMapSizeX(), regionConfig->getMapSizeY(),
                                                   surfaceZLevel);
    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    modelFactory->setRegionGenerator(regionGenerator);

    shared->getLog()->debug(getName(), "Demo loaded");
    return false;
}

void frts::VanillaDemoTickable::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

bool frts::VanillaDemoTickable::preInit(frts::SharedManagerPtr)
{
    return false;
}

void frts::VanillaDemoTickable::tick(frts::SharedManagerPtr shared)
{
    if (shared->getFrame()->getRunTime() >= fromMilliseconds(60 * 1000))
    {
        auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
        commandFactory->makeCommand(shared->makeId(CommandIds::quit()), shared)->execute(shared);
    }
}

void frts::VanillaDemoTickable::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
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
