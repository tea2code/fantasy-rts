#include "SortOrderImpl.h"

frts::SortOrderImpl::SortOrderImpl(IdPtr type)
    : sortOrder{0}, type{type}
{

}

frts::IdPtr frts::SortOrderImpl::getComponentType() const
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
