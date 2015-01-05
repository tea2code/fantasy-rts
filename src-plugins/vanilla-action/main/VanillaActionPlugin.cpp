#include "VanillaActionPlugin.h"

#include "ActionHandler.h"
#include "impl/ActionManagerImpl.h"


frts::VanillaActionPlugin::VanillaActionPlugin()
{
}

frts::ActionHandlerPtr frts::VanillaActionPlugin::getActionHandler()
{
    if (actionHandler == nullptr)
    {
        actionHandler = makeActionHandler();
    }
    return actionHandler;
}

frts::ModulePtr frts::VanillaActionPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == ActionManagerImpl::identifier())
    {
        result = makeActionManager(getActionHandler());
    }
    else if (id->toString() == ActionHandler::identifier())
    {
        result = getActionHandler();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaActionPlugin)
