#include "CommandConfigImpl.h"

#include <main/CommandIds.h>


frts::CommandConfigImpl::CommandConfigImpl()
    : BaseDataValue(CommandIds::commandConfig(), 1, CommandIds::commandConfig(), 1)
{}

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
