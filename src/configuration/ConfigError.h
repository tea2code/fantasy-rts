#ifndef CONFIGERROR_H
#define CONFIGERROR_H

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if a config value has the wrong type and can not be
     * converted.
     */
    class ConversionError : public std::runtime_error
    {
    public:
        ConversionError(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Thrown if a config file is not found.
     */
    class FileNotFoundError : public std::runtime_error
    {
    public:
        FileNotFoundError(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Thrown if a config value is missing.
     */
    class MissingValueError : public std::runtime_error
    {
    public:
        MissingValueError(const std::string& msg) : std::runtime_error(msg) {}
    };
}

#endif // CONFIGERROR_H
