#ifndef FRTS_ID_H
#define FRTS_ID_H

#include "SharedPtr.h"

#include <functional>
#include <string>


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
    };

    /**
     * @brief Compare equality.
     * @param lhs First id.
     * @param rhs Second id.
     * @return True if id are equal.
     */
    inline bool operator==(IdPtr lhs, IdPtr rhs)
    {
        return *lhs == *rhs;
    }

    /**
     * @brief Compare inequality.
     * @param lhs First id.
     * @param rhs Second id.
     * @return True if id are not equal.
     */
    inline bool operator!=(IdPtr lhs, IdPtr rhs)
    {
        return *lhs != *rhs;
    }

    /**
     * @brief Hash function object for Ids.
     */
    struct IdHash
    {
        std::size_t operator() (IdPtr id) const
        {
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
}

#endif // FRTS_ID_H
