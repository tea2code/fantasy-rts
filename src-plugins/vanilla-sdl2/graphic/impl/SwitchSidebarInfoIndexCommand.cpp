#include "SwitchSidebarInfoIndexCommand.h"

#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>


frts::SwitchSidebarInfoIndexCommand::SwitchSidebarInfoIndexCommand(const IdPtr& commandType, int stepSize)
    : commandType{commandType}, stepSize{stepSize}
{}

void frts::SwitchSidebarInfoIndexCommand::execute(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    gd->setSidebarInfoIndex(gd->getSidebarInfoIndex() + stepSize);
}

frts::IdPtr frts::SwitchSidebarInfoIndexCommand::getCommandType() const
{
    return commandType;
}

void frts::SwitchSidebarInfoIndexCommand::undo(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    gd->setSidebarInfoIndex(gd->getSidebarInfoIndex() - stepSize);
}
