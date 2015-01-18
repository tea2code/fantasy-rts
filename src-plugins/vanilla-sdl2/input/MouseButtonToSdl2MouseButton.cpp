#include "MouseButtonToSdl2MouseButton.h"

#include <SDL2/SDL.h>

#include <map>


std::uint8_t frts::mouseButtonToSdl2MouseButton(MouseButton mouseButton)
{
    static std::map<MouseButton, std::uint8_t> mapping = {
        {MouseButton::Left, SDL_BUTTON_LEFT},
        {MouseButton::Middle, SDL_BUTTON_MIDDLE},
        {MouseButton::Right, SDL_BUTTON_RIGHT},
        {MouseButton::X1, SDL_BUTTON_X1},
        {MouseButton::X2, SDL_BUTTON_X2},
    };
    return mapping.at(mouseButton);
}
