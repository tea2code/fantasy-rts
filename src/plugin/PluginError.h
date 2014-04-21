#ifndef FRTS_PLUGINERROR_H
#define FRTS_PLUGINERROR_H

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

    /**
     * @brief Thrown if a library version is out dated.
     */
    class LibraryOutDated : public std::runtime_error
    {
    public:
        LibraryOutDated(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Thrown if a module was not found.
     */
    class ModuleNotFound : public std::runtime_error
    {
    public:
        ModuleNotFound(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // FRTS_PLUGINERROR_H
