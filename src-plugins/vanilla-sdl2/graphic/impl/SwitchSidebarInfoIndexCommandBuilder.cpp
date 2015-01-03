#include "SwitchSidebarInfoIndexCommandBuilder.h"

#include "SwitchSidebarInfoIndexCommand.h"


frts::SwitchSidebarInfoIndexCommandBuilder::SwitchSidebarInfoIndexCommandBuilder(IdPtr commandType, int stepSize)
    : commandType{commandType}, stepSize{stepSize}
{

}

frts::CommandPtr frts::SwitchSidebarInfoIndexCommandBuilder::build(SharedManagerPtr)
{
    return makeSwitchSidebarInfoIndexCommand(commandType, stepSize);
}
