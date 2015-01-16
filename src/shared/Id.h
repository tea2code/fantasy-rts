#ifndef FRTS_ID_H
#define FRTS_ID_H

#include "SharedPtr.h"

#include <functional>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>


namespace frts
{
    /**
     * @brief Represents an Id.
     */
    class Id
    {
    public:
        virtual ~Id() {}

        /**
         * @brief Calculate hash of id.
         * @return The hash.
         */
        virtual std::size_t hash() const = 0;

        /**
         * @brief Get the string representation of this Id.
         * @return The string representation.
         */
        virtual std::string toString() const = 0;

        virtual bool operator==(const Id& rhs) = 0;
        virtual bool operator!=(const Id& rhs) = 0;
        virtual bool operator<(const Id& rhs) = 0;
    };

    /**
     * @brief Compare equality.
     * @param lhs First id.
     * @param rhs Second id.
     * @return True if id are equal.
     */
    inline bool operator==(const IdPtr& lhs, const IdPtr& rhs)
    {
        bool lhsNull = (lhs == nullptr);
        bool rhsNull = (rhs == nullptr);
        return (lhsNull && rhsNull) || (!lhsNull && !rhsNull && *lhs == *rhs);
    }

    /**
     * @brief Compare inequality.
     * @param lhs First id.
     * @param rhs Second id.
     * @return True if id are not equal.
     */
    inline bool operator!=(const IdPtr& lhs, const IdPtr& rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Compare less.
     * @param lhs First id.
     * @param rhs Second id.
     * @return True if lhs is less than rhs.
     */
    inline bool operator<(const IdPtr& lhs, const IdPtr& rhs)
    {
        bool lhsNull = (lhs == nullptr);
        bool rhsNull = (rhs == nullptr);
        return (lhsNull && !rhsNull) || (!lhsNull && !rhsNull && *lhs < *rhs);
    }
}

namespace std
{
    /**
     * @brief Hash for ids.
     */
    template <>
    struct hash<frts::IdPtr>
    {
        size_t operator()(const frts::IdPtr& id) const
        {
            if (id == nullptr)
            {
                return 0;
            }
            return id->hash();
        }
    };
}

namespace frts
{
    /**
     * @brief Set of IDs.
     */
    using IdSet = std::set<IdPtr>;

    /**
     * @brief Unordered set of IDs.
     */
    using IdUnorderedSet = std::unordered_set<IdPtr>;

    /**
     * @brief Vector of IDs.
     */
    using IdVector = std::vector<IdPtr>;
}

#endif // FRTS_ID_H
