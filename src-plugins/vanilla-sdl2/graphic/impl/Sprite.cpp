#include "Sprite.h"


frts::Sprite::Sprite(IdPtr image, int height, int width, int x, int y, double chance)
    : chance{chance}, height{height}, image{image}, width{width}, x{x}, y{y}
{
}

double frts::Sprite::getChance() const
{
    return chance;
}

int frts::Sprite::getHeight() const
{
    return height;
}

frts::IdPtr frts::Sprite::getImage() const
{
    return image;
}

int frts::Sprite::getWidth() const
{
    return width;
}

int frts::Sprite::getX() const
{
    return x;
}

int frts::Sprite::getY() const
{
    return y;
}
