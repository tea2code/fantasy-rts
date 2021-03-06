#ifndef FRTS_MODELERROR_H
#define FRTS_MODELERROR_H

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if a component builder is unknown/not registered.
     */
    class UnknownComponentBuilderError : public std::runtime_error
    {
    public:
        UnknownComponentBuilderError(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Thrown if there is no configuration for an entity.
     */
    class UnknownEntityError : public std::runtime_error
    {
    public:
        UnknownEntityError(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Thrown if a map parser is unknown/not registered.
     */
    class UnknownMapParserError : public std::runtime_error
    {
    public:
        UnknownMapParserError(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // FRTS_MODELERROR_H
