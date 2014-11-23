#include "MoveCursorCommandBuilder.h"

#include "MoveCursorCommand.h"


frts::MoveCursorCommandBuilder::MoveCursorCommandBuilder(IdPtr commandType, Point::value x, Point::value y, Point::value z)
    : commandType{commandType}, x{x}, y{y}, z{z}
{
}

frts::CommandPtr frts::MoveCursorCommandBuilder::build(SharedManagerPtr)
{
    return makeMoveCursorCommand(commandType, x, y, z);
}
