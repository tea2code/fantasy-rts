#include "StopJobsCommandBuilder.h"

#include "StopJobsCommand.h"


frts::StopJobsCommandBuilder::StopJobsCommandBuilder(const IdPtr& commandType)
    : commandType{commandType}
{

}

frts::StopJobsCommandBuilder::~StopJobsCommandBuilder()
{

}

frts::CommandPtr frts::StopJobsCommandBuilder::build(const SharedManagerPtr&)
{
    return makeStopJobsCommand(commandType, node);
}

void frts::StopJobsCommandBuilder::setSettings(const ConfigNodePtr& node)
{
    assert(node != nullptr);

    this->node = node;
}
