#include "MoveScreenCommandBuilder.h"

#include "MoveScreenCommand.h"


frts::MoveScreenCommandBuilder::MoveScreenCommandBuilder(const IdPtr& commandType, Point::value x, Point::value y, Point::value z)
    : commandType{commandType}, x{x}, y{y}, z{z}
{
}

frts::CommandPtr frts::MoveScreenCommandBuilder::build(const SharedManagerPtr&)
{
    return makeMoveScreenCommand(commandType, x, y, z);
}
