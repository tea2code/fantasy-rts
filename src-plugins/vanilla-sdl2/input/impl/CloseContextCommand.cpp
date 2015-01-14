#include "CloseContextCommand.h"

#include <input/InputHandler.h>
#include <main/Sdl2Ids.h>


frts::CloseContextCommand::CloseContextCommand(IdPtr commandType)
    : commandType{commandType}
{

}

frts::CloseContextCommand::~CloseContextCommand()
{

}

void frts::CloseContextCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto ih = getUtility<InputHandler>(shared, Sdl2Ids::inputHandler());
    ih->closeCurrentContext();
}

frts::IdPtr frts::CloseContextCommand::getCommandType() const
{
    return commandType;
}
void frts::CloseContextCommand::undo(SharedManagerPtr)
{
    // Undo not supported.
}