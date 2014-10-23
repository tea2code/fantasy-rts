#include "RenderableImpl.h"


frts::RenderableImpl::RenderableImpl(IdPtr type)
    : spriteIndex{0}, type{type}
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
