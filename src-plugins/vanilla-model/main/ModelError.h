#ifndef FRTS_MODELERROR_H
#define FRTS_MODELERROR_H

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if a component builder is unknown/not registered.
     */
    class UnknownBuilderError : public std::runtime_error
    {
    public:
        UnknownBuilderError(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // FRTS_MODELERROR_H
