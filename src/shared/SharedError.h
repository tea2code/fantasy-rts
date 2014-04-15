#ifndef FRTS_SHAREDERROR_H
#define FRTS_SHAREDERROR_H

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if a id is existing.
     */
    class IdNotFoundError : public std::runtime_error
    {
    public:
        IdNotFoundError(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // FRTS_SHAREDERROR_H
