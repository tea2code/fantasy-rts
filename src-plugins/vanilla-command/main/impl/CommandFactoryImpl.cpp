#include "CommandFactoryImpl.h"

#include <commandbuilder/QuitCommandBuilder.h>
#include <commandbuilder/UndoCommandBuilder.h>
#include <main/CommandError.h>
#include <main/CommandIds.h>
#include <main/impl/CommandConfigImpl.h>
#include <frts/configuration>

#include <boost/format.hpp>

#include <cassert>
#include <utility>


frts::CommandFactoryImpl::CommandFactoryImpl()
{
}

void frts::CommandFactoryImpl::addToUndo(CommandPtr command, SharedManagerPtr shared)
{
    assert(command != nullptr);
    assert(shared != nullptr);

    auto cc = getDataValue<CommandConfig>(shared, CommandIds::commandConfig());
    auto notUndoableCommands = cc->getNotUndoableCommands();
    if (notUndoableCommands.find(command->getCommandType()) != notUndoableCommands.end())
    {
        return;
    }

    undoQueue.push_back(command);
    while (undoQueue.size() > cc->getNumUndo())
    {
        undoQueue.pop_front();
    }
}

void frts::CommandFactoryImpl::checkRequiredData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), CommandIds::commandConfig(), 1, shared);
}

bool frts::CommandFactoryImpl::createData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto cc = makeCommandConfig();
    shared->setDataValue(shared->makeId(CommandIds::commandConfig()), cc);
    cc->setNumUndo(10); // Default value.

    return false;
}

std::string frts::CommandFactoryImpl::getName() const
{
    return CommandIds::commandFactory();
}

std::vector<std::string> frts::CommandFactoryImpl::getSupportedConfig()
{
    return {"command"};
}

std::string frts::CommandFactoryImpl::getTypeName() const
{
    return getName();
}

int frts::CommandFactoryImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::CommandFactoryImpl::getVersion() const
{
    return 1;
}

bool frts::CommandFactoryImpl::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // Commands:
    // Quit.
    auto commandId = shared->makeId(CommandIds::quit());
    registerCommandBuilder(commandId, makeQuitCommandBuilder(commandId));

    // Undo.
    commandId = shared->makeId(CommandIds::undo());
    registerCommandBuilder(commandId, makeUndoCommandBuilder(commandId));

    isInit = true;
    return false;
}

bool frts::CommandFactoryImpl::isInitialized() const
{
    return isInit;
}

bool frts::CommandFactoryImpl::isPreInitialized() const
{
    return isPreInit;
}

frts::CommandPtr frts::CommandFactoryImpl::makeCommand(IdPtr builderId, SharedManagerPtr shared)
{
    assert(builderId != nullptr);
    assert(shared != nullptr);

    auto it = commandBuilders.find(builderId);
    if(it != commandBuilders.end())
    {
        return it->second->build(shared);
    }
    else
    {
        auto msg = boost::format(R"(%2%: No command builder is registered for ID "%1%".)") % builderId->toString() % getName();
        throw UnknownCommandBuilderError(msg.str());
    }
}

void frts::CommandFactoryImpl::parseConfig(const std::string&, ConfigNodePtr node, SharedManagerPtr shared)
{
    assert(node != nullptr);
    assert(shared != nullptr);

    auto cc = getDataValue<CommandConfig>(shared, CommandIds::commandConfig());

    if (node->has("num_undo"))
    {
        cc->setNumUndo(node->getInteger("num_undo", cc->getNumUndo()));
    }

    if (node->has("undo_blacklist"))
    {
        auto commands = cc->getNotUndoableCommands();
        for (auto& idStr : node->getStrings("undo_blacklist"))
        {
            auto command = shared->makeId(idStr);
            commands.insert(command);
        }
        cc->setNotUndoableCommands(commands);
    }
}

bool frts::CommandFactoryImpl::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}


void frts::CommandFactoryImpl::registerCommandBuilder(IdPtr builderId, CommandBuilderPtr builder)
{
    assert(builderId != nullptr);
    assert(builder != nullptr);

    commandBuilders.insert(std::make_pair(builderId, builder));
}

void frts::CommandFactoryImpl::undoLastCommand(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    if (!undoQueue.empty())
    {
        undoQueue.back()->undo(shared);
        undoQueue.pop_back();
    }
}

void frts::CommandFactoryImpl::validateData(SharedManagerPtr)
{
}

void frts::CommandFactoryImpl::validateModules(SharedManagerPtr)
{

}
