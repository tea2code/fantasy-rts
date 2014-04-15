#include "IdImpl.h"


frts::IdImpl::IdImpl(const std::string& str)
    : str{str}
{
}

frts::IdImpl::~IdImpl()
{
}

std::string frts::IdImpl::toString() const noexcept
{
    return str;
}

bool frts::IdImpl::operator==(const Id& rhs)
{
    return str == dynamic_cast<const IdImpl&>(rhs).str;
}

bool frts::IdImpl::operator!=(const Id& rhs)
{
    return str != dynamic_cast<const IdImpl&>(rhs).str;
}
