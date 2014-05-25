#include "SortOrderImpl.h"

#include <entity/ComponentIds.h>

frts::SortOrderImpl::SortOrderImpl(SharedManagerPtr shared)
    : type{shared->makeId(ComponentIds::sortOrder())}
{

}

frts::IdPtr frts::SortOrderImpl::getComponentType()
{
    return type;
}

int frts::SortOrderImpl::getSortOrder() const
{
    return sortOrder;
}

void frts::SortOrderImpl::setSortOrder(int sortOrder)
{
    this->sortOrder = sortOrder;
}
