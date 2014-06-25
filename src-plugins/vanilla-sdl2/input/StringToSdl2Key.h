#ifndef FRTS_STRINGTOSDL2KEY_H
#define FRTS_STRINGTOSDL2KEY_H

#include <SDL2/SDL.h>

#include <string>


namespace frts
{
    /**
     * @brief Konvert string to SDL2 key type.
     * @param keyString The string representing a key.
     * @return The SDL2 key type.
     */
    SDL_Keycode stringToSdl2Key(std::string keyString);
}

#endif // FRTS_STRINGTOSDL2KEY_H
