#ifndef ID_H
#define ID_H

#include <string>

namespace frts
{
    /**
     * @brief Represents an id.
     */
    class Id
    {
    public:
        /**
         * @brief Create id from string representation.
         * @param str The string representation of this id.
         * @return The id.
         */
        static Id from(const std::string& str)
        {
            return Id(str);
        }

        /**
         * @brief Get the string representation of this id.
         * @return The string representation.
         */
        std::string toString()
        {
            return str;
        }

        bool operator==(const Id& rhs)
        {
            return str == rhs.str;
        }

        bool operator!=(const Id& rhs)
        {
            return str != rhs.str;
        }

    private:
        std::string str;

    private:
        Id(const std::string& str) : str{str} {}
    };
}

#endif // ID_H
