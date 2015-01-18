#include "StringToSdl2MouseButton.h"

#include <boost/format.hpp>
#include <SDL2/SDL.h>

#include <algorithm>
#include <unordered_map>


std::string frts::mouseButtonStringPrefix()
{
    return "mouse_";
}

std::uint8_t frts::stringToSdl2MouseButton(std::string mouseButtonString)
{
    static std::unordered_map<std::string, std::uint8_t> mapping = {
        {mouseButtonStringPrefix() + "left", SDL_BUTTON_LEFT},
        {mouseButtonStringPrefix() + "middle", SDL_BUTTON_MIDDLE},
        {mouseButtonStringPrefix() + "right", SDL_BUTTON_RIGHT},
        {mouseButtonStringPrefix() + "x1", SDL_BUTTON_X1},
        {mouseButtonStringPrefix() + "x2", SDL_BUTTON_X2}
    };
    std::transform(mouseButtonString.begin(), mouseButtonString.end(), mouseButtonString.begin(), ::tolower);
    auto it = mapping.find(mouseButtonString);
    if (it != mapping.end())
    {
        return it->second;
    }
    else
    {
        auto msg = boost::format(R"(Unknown mouse button "%1%".)") % mouseButtonString;
        throw UnknownMouseButtonString(msg.str());
    }
}
