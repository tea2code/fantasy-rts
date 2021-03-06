#include "SelectionDataImpl.h"

#include <main/Sdl2Ids.h>


frts::SelectionDataImpl::SelectionDataImpl()
    : BaseDataValue(Sdl2Ids::selectionData(), 1, Sdl2Ids::selectionData(), 1)
{
    resetSelection();
}

frts::SelectionDataImpl::~SelectionDataImpl()
{

}

frts::PointVector frts::SelectionDataImpl::getSelection(const SharedManagerPtr& shared) const
{
    PointVector result;
    if (start == nullptr || end == nullptr)
    {
        return result;
    }

    Point::value minX = std::min(start->getX(), end->getX());
    Point::value maxX = std::max(start->getX(), end->getX());
    Point::value minY = std::min(start->getY(), end->getY());
    Point::value maxY = std::max(start->getY(), end->getY());
    Point::value minZ = std::min(start->getZ(), end->getZ());
    Point::value maxZ = std::max(start->getZ(), end->getZ());

    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    for (Point::value x = minX; x <= maxX; ++x)
    {
        for (Point::value y = minY; y <= maxY; ++y)
        {
            for (Point::value z = minZ; z <= maxZ; ++z)
            {
                result.push_back(mf->makePoint(x, y, z));
            }
        }
    }
    return result;
}

frts::PointPtr frts::SelectionDataImpl::getSelectionEnd() const
{
    return end;
}

frts::IdPtr frts::SelectionDataImpl::getSelectionEntityId() const
{
    return selectionEntityId;
}

std::vector<frts::EntityPtr> frts::SelectionDataImpl::getSelectionEntities() const
{
    return selectionEntities;
}

frts::PointPtr frts::SelectionDataImpl::getSelectionStart() const
{
    return start;
}

bool frts::SelectionDataImpl::isSelecting() const
{
    return currentlySelecting;
}

void frts::SelectionDataImpl::resetSelection()
{
    start = nullptr;
    end = nullptr;
    selectionEntities.clear();
    currentlySelecting = false;
}

void frts::SelectionDataImpl::setIsSelecting(bool isSelecting)
{
    this->currentlySelecting = isSelecting;
}

void frts::SelectionDataImpl::setSelectionEnd(const PointPtr& pos)
{
    assert(pos != nullptr);

    this->end = pos;
}

void frts::SelectionDataImpl::setSelectionEntityId(const IdPtr& entityId)
{
    assert(entityId != nullptr);

    this->selectionEntityId = entityId;
}

void frts::SelectionDataImpl::setSelectionEntities(const EntityVector& entities)
{
    this->selectionEntities = entities;
}

void frts::SelectionDataImpl::setSelectionStart(const PointPtr& pos)
{
    assert(pos != nullptr);

    this->start = pos;
}
