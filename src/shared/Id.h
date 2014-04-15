#ifndef ID_H
#define ID_H

#include <memory>
#include <string>


namespace frts
{
    class Id;

    /**
     * @brief Pointer to Id.
     */
    using IdPtr = std::shared_ptr<Id>;

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
        virtual std::string toString() const noexcept = 0;

        virtual bool operator==(const Id& rhs) = 0;
        virtual bool operator!=(const Id& rhs) = 0;
    };
}

#endif // ID_H
