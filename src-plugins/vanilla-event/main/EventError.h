#ifndef FRTS_EVENTERROR_H
#define FRTS_EVENTERROR_H

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if a event value builder is unknown/not registered.
     */
    class UnknownEventValueBuilderError : public std::runtime_error
    {
    public:
        UnknownEventValueBuilderError(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // FRTS_EVENTERROR_H
