#ifndef FRTS_IDIMPL_H
#define FRTS_IDIMPL_H

#include "Id.h"


namespace frts
{
    class IdImpl : public Id
    {
    public:
        IdImpl(const std::string& str);
        ~IdImpl() override;

        std::string toString() const noexcept override;

        bool operator==(const Id& rhs) override;
        bool operator!=(const Id& rhs) override;

    private:
        std::string str;
    };
}

#endif // FRTS_IDIMPL_H
