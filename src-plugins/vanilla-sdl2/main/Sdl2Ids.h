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

        static std::string moveCommandWest()
        {
            return "frts.vanillasdl2.command.movescreen.west";
        }

        static std::string moveCommandEast()
        {
            return "frts.vanillasdl2.command.movescreen.east";
        }

        static std::string moveCommandNorth()
        {
            return "frts.vanillasdl2.command.movescreen.north";
        }

        static std::string moveCommandSouth()
        {
            return "frts.vanillasdl2.command.movescreen.south";
        }

        static std::string moveCommandUp()
        {
            return "frts.vanillasdl2.command.movescreen.up";
        }

        static std::string moveCommandDown()
        {
            return "frts.vanillasdl2.command.movescreen.down";
        }

        static std::string renderable()
        {
            return "frts.vanillasdl2.entity.component.renderable";
        }
    };
}

#endif // FRTS_SDL2IDS_H
