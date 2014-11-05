#include "CommandFactoryImpl.h"

#include <commandbuilder/QuitCommandBuilder.h>
#include <main/CommandError.h>
#include <main/CommandIds.h>

#include <boost/format.hpp>


frts::CommandFactoryImpl::CommandFactoryImpl()
{
}

bool frts::CommandFactoryImpl::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::CommandFactoryImpl::getName() const
{
    return CommandIds::commandFactory();
}

std::vector<std::string> frts::CommandFactoryImpl::getSupportedConfig()
{
    return {};
}

std::string frts::CommandFactoryImpl::getTypeName() const
{
    return getName();
}

int frts::CommandFactoryImpl::getTypeVersion() const
{
    return 1;
}

int frts::CommandFactoryImpl::getVersion() const
{
    return 1;
}

bool frts::CommandFactoryImpl::init(SharedManagerPtr shared)
{
    // Commands:
    // Quit.
    IdPtr quitId = shared->makeId(CommandIds::quit());
    CommandBuilderPtr commandBuilder = makeQuitCommandBuilder();
    registerCommandBuilder(quitId, commandBuilder);

    return false;
}


frts::CommandPtr frts::CommandFactoryImpl::makeCommand(IdPtr builderId, SharedManagerPtr shared)
{
    auto it = commandBuilders.find(builderId);
    if(it != commandBuilders.end())
    {
        return it->second->build(shared);
    }
    else
    {
        auto msg = boost::format(R"(No command builder is registered for ID "%1%".)") % builderId->toString();
        throw UnknownCommandBuilderError(msg.str());
    }
}

void frts::CommandFactoryImpl::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::CommandFactoryImpl::preInit(SharedManagerPtr)
{
    return false;
}


void frts::CommandFactoryImpl::registerCommandBuilder(IdPtr builderId, CommandBuilderPtr builder)
{
    commandBuilders[builderId] = builder;
}

void frts::CommandFactoryImpl::validateData(SharedManagerPtr)
{

}

void frts::CommandFactoryImpl::validateModules(SharedManagerPtr)
{

}
