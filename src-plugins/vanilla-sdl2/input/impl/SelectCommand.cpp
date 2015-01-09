#include "SelectCommand.h"

#include "SelectionHelper.h"
#include <input/SelectionData.h>
#include <main/Sdl2Ids.h>


frts::SelectCommand::SelectCommand(IdPtr commandType)
    : commandType{commandType}
{

}

frts::SelectCommand::~SelectCommand()
{

}

void frts::SelectCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());

    if (sd->isSelecting())
    {
        endSelection(shared);
    }
    else
    {
        newSelection(shared);
    }
}

frts::IdPtr frts::SelectCommand::getCommandType() const
{
    return commandType;
}

void frts::SelectCommand::undo(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());

    if (sd->isSelecting())
    {
        stopSelection(shared);
    }
}
