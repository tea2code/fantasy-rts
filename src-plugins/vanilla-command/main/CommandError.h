#ifndef FRTS_COMMANDERROR_H
#define FRTS_COMMANDERROR_H

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if a command builder is unknown/not registered.
     */
    class UnknownCommandBuilderError : public std::runtime_error
    {
    public:
        UnknownCommandBuilderError(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // FRTS_COMMANDERROR_H
