#include "SwitchSidebarInfoIndexCommand.h"

#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>


frts::SwitchSidebarInfoIndexCommand::SwitchSidebarInfoIndexCommand(IdPtr commandType, int stepSize)
    : commandType{commandType}, stepSize{stepSize}
{}

void frts::SwitchSidebarInfoIndexCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    gd->setSidebarInfoIndex(gd->getSidebarInfoIndex() + stepSize);
}

frts::IdPtr frts::SwitchSidebarInfoIndexCommand::getCommandType() const
{
    return commandType;
}

void frts::SwitchSidebarInfoIndexCommand::undo(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    gd->setSidebarInfoIndex(gd->getSidebarInfoIndex() - stepSize);
}
