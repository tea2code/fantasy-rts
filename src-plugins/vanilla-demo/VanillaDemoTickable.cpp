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
    // Do not adopt this practice. Use frame number only for quick trial and error.
    int fps = (fromMilliseconds(1000) / shared->getFrame()->getDeltaTime());
    Frame::ticks number = shared->getFrame()->getNumber();

    if (number == 0)
    {
        IdPtr modelFactoryId = shared->makeId("frts/ModelFactory");
        ModelFactoryPtr modelFactory = std::static_pointer_cast<ModelFactory>(shared->getUtility(modelFactoryId));

        IdPtr entityId = shared->makeId("entity.shrub.berry");
        EntityPtr entity = modelFactory->makeEntity(entityId, shared);

        IdPtr componentId = shared->makeId("frts.vanillamodel.entity.component.hasresource");
        HasResourcePtr component = getComponent<HasResource>(componentId, entity);
        IdPtr resourceId = shared->makeId("resource.food");
        if (component->hasResource(resourceId))
        {
            shared->getLog()->debug(getName(), "Berry shrub is configured.");
        }
        else
        {
            shared->getLog()->debug(getName(), "Berry shrub not found. We must starve.");
        }
    }

    if (number % fps == 0)
    {
        shared->getLog()->debug(getName(), "Frame " + std::to_string(number));
    }

    if (shared->getFrame()->getRunTime() >= fromMilliseconds(5 * 1000))
    {
        IdPtr commandFactoryId = shared->makeId("frts/CommandFactory");
        CommandFactoryPtr commandFactory = std::static_pointer_cast<CommandFactory>(shared->getUtility(commandFactoryId));

        IdPtr quitCommandId = shared->makeId(CommandIds::quit());
        commandFactory->makeCommand(quitCommandId, shared)->execute(shared);
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
        IdPtr id = shared->makeId("frts/ModelFactory");
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility ModelFactory not found.");
    }
}
