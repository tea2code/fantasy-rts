#include "VanillaDemoTickable.h"

#include <frts/shared>
#include <frts/vanillamodel>


frts::VanillaDemoTickable::VanillaDemoTickable::VanillaDemoTickable()
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

void frts::VanillaDemoTickable::tick(frts::SharedManagerPtr shared)
{
    // Do not adopt this practice. Use frame number only for quick trial and error.
    int fps = (fromMilliseconds(1000) / shared->getFrame()->getDeltaTime());
    Frame::ticks number = shared->getFrame()->getNumber();
    if (number % fps == 0)
    {
        shared->getLog()->debug(getName(), "Frame " + std::to_string(number));
    }

    if (shared->getFrame()->getRunTime() >= fromMilliseconds(5 * 1000))
    {
        shared->setQuitApplication(true);
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
        IdPtr id = shared->makeId("ModelFactory");
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility ModelFactory not found.");
    }
}