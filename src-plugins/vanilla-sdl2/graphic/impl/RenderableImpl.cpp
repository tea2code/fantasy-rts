#include "RenderableImpl.h"


frts::RenderableImpl::RenderableImpl(IdPtr type)
    : type{type}
{}

frts::IdPtr frts::RenderableImpl::getComponentType() const
{
    return type;
}

frts::IdPtr frts::RenderableImpl::getSprite() const
{
    return sprite;
}

int frts::RenderableImpl::getSpriteIndex() const
{
    return spriteIndex;
}

unsigned int frts::RenderableImpl::getTransparency() const
{
    return transparency;
}

bool frts::RenderableImpl::isSpriteIndexSet() const
{
    return spriteIndexSet;
}

void frts::RenderableImpl::setSprite(IdPtr id)
{
    sprite = id;
}

void frts::RenderableImpl::setSpriteIndex(int index)
{
    spriteIndex = index;
    spriteIndexSet = true;
}

void frts::RenderableImpl::setTransparency(unsigned int transparency)
{
    this->transparency = transparency;
}
