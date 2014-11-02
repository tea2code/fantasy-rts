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
            return "frts.vanillasdl2.graphic.graphicdata";
        }

        static std::string eventHandler()
        {
            return "frts/EventHandler";
        }

        static std::string inputHandler()
        {
            return "frts/InputHandler";
        }

        static std::string renderable()
        {
            return "frts.vanillasdl2.entity.component.renderable";
        }

        static std::string sdl2Renderer()
        {
            return "frts/SDL2Renderer";
        }
    };
}

#endif // FRTS_SDL2IDS_H
