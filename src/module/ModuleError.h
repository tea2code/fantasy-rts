#ifndef MODULEERROR_H
#define MODULEERROR_H

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown by a module if a data value doesn't match the expected
     * interface.
     */
    class DataViolation : public std::runtime_error
    {
    public:
        DataViolation(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Thrown by a module if the shared manager doesn't contain expected
     * modules or if it contains modules which souldn't be loaded.
     */
    class ModuleViolation : public std::runtime_error
    {
    public:
        ModuleViolation(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // MODULEERROR_H
