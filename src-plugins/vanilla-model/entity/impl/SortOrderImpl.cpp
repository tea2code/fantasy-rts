#include "SortOrderImpl.h"

frts::SortOrderImpl::SortOrderImpl(IdPtr type)
    : type{type}
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
