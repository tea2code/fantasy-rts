#ifndef FRTS_SDL2IDS_H
#define FRTS_SDL2IDS_H

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of SDL2 ID strings.
     */
    class Sdl2Ids
    {
    public:
        static std::string graphicData()
        {
            return "frts::GraphicData";
        }

        static std::string inputHandler()
        {
            return "frts::InputHandler";
        }

        static std::string renderable()
        {
            return "frts.vanillasdl2.entity.component.renderable";
        }
    };
}

#endif // FRTS_SDL2IDS_H
