#include "StopJobsCommandBuilder.h"

#include "StopJobsCommand.h"


frts::StopJobsCommandBuilder::StopJobsCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{

}

frts::StopJobsCommandBuilder::~StopJobsCommandBuilder()
{

}

frts::CommandPtr frts::StopJobsCommandBuilder::build(SharedManagerPtr)
{
    return makeStopJobsCommand(commandType, node);
}

void frts::StopJobsCommandBuilder::setSettings(ConfigNodePtr node)
{
    assert(node != nullptr);

    this->node = node;
}
