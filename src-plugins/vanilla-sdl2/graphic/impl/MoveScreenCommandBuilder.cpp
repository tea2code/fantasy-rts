#include "MoveScreenCommandBuilder.h"

#include "MoveScreenCommand.h"


frts::MoveScreenCommandBuilder::MoveScreenCommandBuilder(Point::value x, Point::value y, Point::value z)
    : x{x}, y{y}, z{z}
{
}

frts::CommandPtr frts::MoveScreenCommandBuilder::build(SharedManagerPtr)
{
    return makeMoveScreenCommand(x, y, z);
}
