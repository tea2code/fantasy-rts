#ifndef FRTS_STRINGTOSDL2KEY_H
#define FRTS_STRINGTOSDL2KEY_H

#include <SDL2/SDL.h>

#include <stdexcept>
#include <string>


namespace frts
{
    /**
     * @brief Thrown if key string is unknown.
     */
    class UnknownKeyString : public std::runtime_error
    {
    public:
        UnknownKeyString(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief Konvert string to SDL2 key type.
     * @throws UnknownKeyString if key string is unknown.
     * @param keyString The string representing a key.
     * @return The SDL2 key type.
     */
    SDL_Keycode stringToSdl2Key(std::string keyString);
}

#endif // FRTS_STRINGTOSDL2KEY_H
