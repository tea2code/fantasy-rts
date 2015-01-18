#ifndef FRTS_STRINGTOSDL2MOUSEBUTTON_H
#define FRTS_STRINGTOSDL2MOUSEBUTTON_H

#include <cstdint>
#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if mouse button string is unknown.
     */
    class UnknownMouseButtonString : public std::runtime_error
    {
    public:
        UnknownMouseButtonString(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Returns the string prefix used for mouse buttons. Can be used to differentiate
     *        between mouse button strings and key strings.
     * @return The mouse button string prefix in all lower case.
     */
    std::string mouseButtonStringPrefix();

    /**
     * @brief Konvert string to SDL2 mouse button type.
     * @throws UnknownMouseButtonString if mouse button string is unknown.
     * @param mouseButtonString The string representing a key.
     * @return The SDL2 mouse button type.
     */
    std::uint8_t stringToSdl2MouseButton(std::string mouseButtonString);
}

#endif // FRTS_STRINGTOSDL2MOUSEBUTTON_H
