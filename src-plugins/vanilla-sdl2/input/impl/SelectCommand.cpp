#include "SelectCommand.h"

#include "SelectionHelper.h"
#include <input/SelectionData.h>
#include <main/Sdl2Ids.h>


frts::SelectCommand::SelectCommand(const IdPtr& commandType)
    : commandType{commandType}
{

}

frts::SelectCommand::~SelectCommand()
{

}

void frts::SelectCommand::execute(const SharedManagerPtr& shared)
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

void frts::SelectCommand::undo(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());

    if (sd->isSelecting())
    {
        stopSelection(shared);
    }
}
