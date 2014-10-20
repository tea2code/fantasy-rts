#include "RenderableImpl.h"


frts::RenderableImpl::RenderableImpl(IdPtr type)
    : spriteIndex{0}, type{type}
{}

void frts::RenderableImpl::addSprite(IdPtr id)
{
    sprites.push_back(id);
}

frts::IdPtr frts::RenderableImpl::getComponentType() const
{
    return type;
}

int frts::RenderableImpl::getNumSprites() const
{
    return sprites.size();
}

frts::IdPtr frts::RenderableImpl::getSprite(int spriteIndex) const
{
    return sprites.at(spriteIndex);
}

int frts::RenderableImpl::getSpriteIndex() const
{
    return spriteIndex;
}

void frts::RenderableImpl::setSpriteIndex(int index)
{
    spriteIndex = index;
}
