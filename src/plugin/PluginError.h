#ifndef PLUGINERROR_H
#define PLUGINERROR_H

#include <stdexcept>
#include <string>

namespace frts
{
    /**
     * @brief Thrown if a library was not found.
     */
    class LibraryNotFound : public std::runtime_error
    {
    public:
        LibraryNotFound(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // PLUGINERROR_H
