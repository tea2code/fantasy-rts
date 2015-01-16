#include "VanillaJobPlugin.h"

#include "impl/JobManagerImpl.h"

#include <frts/shared>


frts::VanillaJobPlugin::VanillaJobPlugin()
{
}

frts::JobHandlerPtr frts::VanillaJobPlugin::getJobHandler()
{
    if (jobHandler == nullptr)
    {
        jobHandler = makeJobHandler();
    }
    return jobHandler;
}

frts::ModulePtr frts::VanillaJobPlugin::getModule(const IdPtr& id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == JobManagerImpl::identifier())
    {
        result = makeJobManager(getJobHandler());
    }
    else if (id->toString() == JobHandler::identifier())
    {
        result = getJobHandler();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaJobPlugin)
