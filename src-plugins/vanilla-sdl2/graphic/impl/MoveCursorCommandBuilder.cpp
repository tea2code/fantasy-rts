#include "MoveCursorCommandBuilder.h"

#include "MoveCursorCommand.h"


frts::MoveCursorCommandBuilder::MoveCursorCommandBuilder(const IdPtr& commandType, Point::value x, Point::value y, Point::value z)
    : commandType{commandType}, x{x}, y{y}, z{z}
{
}

frts::CommandPtr frts::MoveCursorCommandBuilder::build(const SharedManagerPtr&)
{
    return makeMoveCursorCommand(commandType, x, y, z);
}
