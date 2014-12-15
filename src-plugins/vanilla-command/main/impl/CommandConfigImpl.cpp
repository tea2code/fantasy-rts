#include "CommandConfigImpl.h"

#include <main/CommandIds.h>


frts::CommandConfigImpl::CommandConfigImpl()
{}

std::string frts::CommandConfigImpl::getName() const
{
    return CommandIds::commandConfig();
}

frts::IdUnorderedSet frts::CommandConfigImpl::getNotUndoableCommands() const
{
    return notUndoableCommands;
}

unsigned int frts::CommandConfigImpl::getNumUndo() const
{
    return numUndo;
}

void frts::CommandConfigImpl::setNotUndoableCommands(IdUnorderedSet commands)
{
    this->notUndoableCommands = commands;
}

void frts::CommandConfigImpl::setNumUndo(unsigned int numUndo)
{
    this->numUndo = numUndo;
}

std::string frts::CommandConfigImpl::getTypeName() const
{
    return getName();
}

int frts::CommandConfigImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::CommandConfigImpl::getVersion() const
{
    return 1;
}
