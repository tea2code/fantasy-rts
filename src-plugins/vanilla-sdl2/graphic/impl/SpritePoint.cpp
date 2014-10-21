#include "SpritePoint.h"


frts::SpritePoint::SpritePoint(int x, int y, double chance)
    : chance{chance}, x{x}, y{y}
{
}

double frts::SpritePoint::getChance() const
{
    return chance;
}

int frts::SpritePoint::getX() const
{
    return x;
}

int frts::SpritePoint::getY() const
{
    return y;
}
