#include "Sprite.h"


frts::Sprite::Sprite(IdPtr image, int height, int width, std::vector<SpritePoint> spritePoints)
    : height{height}, image{image}, spritePoints{spritePoints}, width{width}
{
}

int frts::Sprite::getHeight() const
{
    return height;
}

frts::IdPtr frts::Sprite::getImage() const
{
    return image;
}

std::vector<frts::SpritePoint> frts::Sprite::getSpritePoints() const
{
    return spritePoints;
}

int frts::Sprite::getWidth() const
{
    return width;
}

int frts::Sprite::getX() const
{
    return spritePoints.at(spritePointIndex).getX();
}

int frts::Sprite::getY() const
{
    return spritePoints.at(spritePointIndex).getY();
}

void frts::Sprite::setSpritePointIndex(int spritePointIndex)
{
        this->spritePointIndex = spritePointIndex;
}
