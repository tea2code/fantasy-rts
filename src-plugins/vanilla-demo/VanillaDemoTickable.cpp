#include "VanillaDemoTickable.h"

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
    return "frts::VanillaDemoTickable";
}

std::vector<std::string> frts::VanillaDemoTickable::getSupportedConfig()
{
    return {};
}

int frts::VanillaDemoTickable::getVersion() const
{
    return 1;
}

bool frts::VanillaDemoTickable::init(frts::SharedManagerPtr shared)
{
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
    if (shared->getFrame()->getRunTime() >= fromMilliseconds(5 * 1000))
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
        getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility ModelFactory not found.");
    }
}
