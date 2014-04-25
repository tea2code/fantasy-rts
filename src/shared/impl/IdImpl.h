#ifndef FRTS_IDIMPL_H
#define FRTS_IDIMPL_H

#include <shared/Id.h>
#include <shared/SharedPtr.h>


namespace frts
{
    class IdImpl : public Id
    {
    public:
        IdImpl(const std::string& str);
        ~IdImpl() override;

        std::string toString() const override;

        bool operator==(const Id& rhs) override;
        bool operator!=(const Id& rhs) override;

    private:
        std::string str;
    };

    IdPtr makeId(const std::string& str);
}

#endif // FRTS_IDIMPL_H
