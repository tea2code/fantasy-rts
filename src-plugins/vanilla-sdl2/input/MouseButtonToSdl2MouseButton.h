#ifndef FRTS_MOUSEBUTTONTOSDL2MOUSEBUTTON_H
#define FRTS_MOUSEBUTTONTOSDL2MOUSEBUTTON_H

#include "MouseButton.h"

#include <cstdint>


namespace frts
{
    /**
     * @brief Konvert mouse button type to SDL2 mouse button type.
     * @param mouseButton The mouse button type.
     * @return The SDL2 mouse button type.
     */
    std::uint8_t mouseButtonToSdl2MouseButton(MouseButton mouseButton);
}

#endif // FRTS_MOUSEBUTTONTOSDL2MOUSEBUTTON_H
