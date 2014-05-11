#include "BlockImpl.h"

#include <algorithm>


frts::BlockImpl::BlockImpl()
    : dynamicEntities{std::make_shared<EntitySet>()},
      resources{std::make_shared<EntitySet>()},
      staticEntities{std::make_shared<EntitySet>()},
      tiles{std::make_shared<EntitySet>()}
{
}

frts::Block::EntitySet frts::BlockImpl::getByType(Entity::Type type) const
{
    return *getPtrByType(type);
}

std::shared_ptr<frts::Block::EntitySet> frts::BlockImpl::getPtrByType(Entity::Type type) const
{
    switch(type)
    {
    case Entity::Type::Dynamic:
        return dynamicEntities;
        break;

    case Entity::Type::Resource:
        return resources;
        break;

    case Entity::Type::Static:
        return staticEntities;
        break;

    case Entity::Type::Tile:
        return tiles;
        break;

    default:
        throw makeUnknownTypeError(type);
    }
}

bool frts::BlockImpl::has(EntityPtr entity) const
{
    auto entitySet = getPtrByType(entity->getType());
    auto itPair = entitySet->equal_range(entity);
    return (std::find(itPair.first, itPair.second, entity) != itPair.second);
}

void frts::BlockImpl::insert(EntityPtr entity)
{
    auto entitySet = getPtrByType(entity->getType());
    entitySet->insert(entity);
}

bool frts::BlockImpl::isBlocking(BlockingPtr blockedBy) const
{
    return isBlocking(getPtrByType(Entity::Type::Static), blockedBy) ||
           isBlocking(getPtrByType(Entity::Type::Dynamic), blockedBy) ||
           isBlocking(getPtrByType(Entity::Type::Resource), blockedBy) ||
           isBlocking(getPtrByType(Entity::Type::Tile), blockedBy);
}

bool frts::BlockImpl::isBlocking(std::shared_ptr<EntitySet> entitySet, BlockingPtr blockedBy) const
{
    bool result = false;
    for (auto entity : *entitySet)
    {
        if (entity->getBlocking()->blocks(blockedBy))
        {
            result = true;
            break;
        }
    }
    return result;
}

void frts::BlockImpl::remove(EntityPtr entity)
{
    auto entitySet = getPtrByType(entity->getType());
    entitySet->erase(entity);
}

std::runtime_error frts::BlockImpl::makeUnknownTypeError(Entity::Type) const
{
    return std::runtime_error("Unknown entity type.");
}
