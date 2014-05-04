#include "VanillaDemoTickable.h"

#include <frts/shared>


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
    int fps = (fromMilliseconds(1000) / toMilliseconds(shared->getFrame()->getDeltaTime()).count()).count();
    if (shared->getFrame()->getNumber() % fps == 0)
    {
        shared->getLog()->debug(getName(), "Frame " + std::to_string(shared->getFrame()->getNumber()));
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

void frts::VanillaDemoTickable::validateModules(frts::SharedManagerPtr)
{
    // Everything is ok.
}
