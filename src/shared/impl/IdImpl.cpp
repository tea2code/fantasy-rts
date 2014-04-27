#include "IdImpl.h"


frts::IdImpl::IdImpl(const std::string& str)
    : str{str}
{
}

frts::IdImpl::~IdImpl()
{
}

std::string frts::IdImpl::toString() const
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

frts::IdPtr frts::makeId(const std::string& str)
{
    // The following commented code is a example implementation of a cached
    // solution which would allow the direct usage of IdPtr for maps...
    // It is not yet usable because it's missing thread safety (for example a
    // mutex around the check and insert.
//    static std::map<std::string, IdPtr> cache;

//    auto it = cache.find(str);
//    if(it == cache.end())
//    {
//        IdPtr id = std::make_shared<frts::IdImpl>(str);
//        cache[str] = id;
//    }

//    return cache.at(str);

    return std::make_shared<frts::IdImpl>(str);
}
