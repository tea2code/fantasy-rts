#include "IdImpl.h"

#ifdef FRTS_FAST_ID
    #include <unordered_map>
    #include <mutex>
#endif


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
#ifdef FRTS_FAST_ID
    return this == &rhs;
#else
    return str == rhs.toString();
#endif
}

bool frts::IdImpl::operator!=(const Id& rhs)
{
    return !(*this == rhs);
}

frts::IdPtr frts::makeId(const std::string& str)
{
#ifdef FRTS_FAST_ID
    static std::mutex mutex;
    static std::unordered_map<std::string, IdPtr> cache;

    std::lock_guard<std::mutex> lock(mutex);
    auto it = cache.find(str);
    if(it == cache.end())
    {
        IdPtr id = std::make_shared<IdImpl>(str);
        cache[str] = id;
        return id;
    }
    else
    {
        return it->second;
    }
#else
    return std::make_shared<IdImpl>(str);
#endif
}
