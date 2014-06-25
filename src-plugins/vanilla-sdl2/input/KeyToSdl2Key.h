#ifndef FRTS_KEYTOSDL2KEY_H
#define FRTS_KEYTOSDL2KEY_H

#include "Key.h"

#include <SDL2/SDL.h>


namespace frts
{
    /**
     * @brief Konvert key type to SDL2 key type.
     * @param key The key type.
     * @return The SDL2 key type.
     */
    SDL_Keycode keyToSdl2Key(Key key);
}

#endif // FRTS_KEYTOSDL2KEY_H
