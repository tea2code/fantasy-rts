#ifndef FRTS_IDIMPL_H
#define FRTS_IDIMPL_H

#include <shared/Id.h>
#include <shared/SharedPtr.h>


namespace frts
{
    /**
     * @brief Id implementation using string comparison. Probably slow.
     */
    class IdImpl : public Id
    {
    public:
        explicit IdImpl(const std::string& str);
        ~IdImpl() override;

        std::size_t hash() const override;
        std::string toString() const override;

        bool operator==(const Id& rhs) override;
        bool operator!=(const Id& rhs) override;
        bool operator<(const Id& rhs) override;

    private:
        size_t cachedHash;
        std::string str;
    };

    IdPtr makeId(const std::string& str);
}

#endif // FRTS_IDIMPL_H
