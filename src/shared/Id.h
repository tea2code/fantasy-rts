#ifndef FRTS_ID_H
#define FRTS_ID_H

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
}

#endif // FRTS_ID_H
