#include "SwitchSidebarInfoIndexCommandBuilder.h"

#include "SwitchSidebarInfoIndexCommand.h"


frts::SwitchSidebarInfoIndexCommandBuilder::SwitchSidebarInfoIndexCommandBuilder(const IdPtr& commandType, int stepSize)
    : commandType{commandType}, stepSize{stepSize}
{

}

frts::CommandPtr frts::SwitchSidebarInfoIndexCommandBuilder::build(const SharedManagerPtr&)
{
    return makeSwitchSidebarInfoIndexCommand(commandType, stepSize);
}
