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
    inline bool operator==(IdPtr lhs, IdPtr rhs)
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
    inline bool operator!=(IdPtr lhs, IdPtr rhs)
    {
        return !(lhs == rhs);
    }

    /**
     * @brief Compare less.
     * @param lhs First id.
     * @param rhs Second id.
     * @return True if lhs is less than rhs.
     */
    inline bool operator<(IdPtr lhs, IdPtr rhs)
    {
        bool lhsNull = (lhs == nullptr);
        bool rhsNull = (rhs == nullptr);
        if (!lhsNull && rhsNull)
        {
            return false;
        }
        return (lhsNull && !rhsNull) || (!lhsNull && !rhsNull && *lhs < *rhs);
    }

    /**
     * @brief Hash function object for Ids.
     */
    struct IdHash
    {
        std::hash<std::string>::result_type operator() (IdPtr id) const
        {
            if (id == nullptr)
            {
                return 0;
            }
            return stringHash(id->toString());
        }

    private:
        std::hash<std::string> stringHash;
    };

    /**
     * @brief Equal to function object for Ids.
     */
    struct IdEqual
    {
        bool operator() (IdPtr lhs, IdPtr rhs) const
        {
            return lhs == rhs;
        }
    };

    /**
     * @brief Less to function object for Ids.
     */
    struct IdLess
    {
        bool operator() (IdPtr lhs, IdPtr rhs) const
        {
            return lhs < rhs;
        }
    };

    /**
     * @brief Set of IDs.
     */
    using IdSet = std::set<IdPtr, IdLess>;

    /**
     * @brief Unordered set of IDs.
     */
    using IdUnorderedSet = std::unordered_set<IdPtr, IdHash, IdEqual>;

    /**
     * @brief Vector of IDs.
     */
    using IdVector = std::vector<IdPtr>;
}

#endif // FRTS_ID_H
