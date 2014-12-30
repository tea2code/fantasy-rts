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
        static std::string eventMoveCursor()
        {
            return "frts.vanillasdl2.event.movecursor";
        }

        static std::string eventMoveCursorPos()
        {
            return "frts.vanillasdl2.event.movecursor.pos";
        }

        static std::string graphicData()
        {
            return "frts::GraphicData";
        }

        static std::string inputHandler()
        {
            return "frts::InputHandler";
        }

        static std::string moveScreenCommandWest()
        {
            return "frts.vanillasdl2.command.movescreen.west";
        }

        static std::string moveScreenCommandEast()
        {
            return "frts.vanillasdl2.command.movescreen.east";
        }

        static std::string moveScreenCommandNorth()
        {
            return "frts.vanillasdl2.command.movescreen.north";
        }

        static std::string moveScreenCommandSouth()
        {
            return "frts.vanillasdl2.command.movescreen.south";
        }

        static std::string moveScreenCommandNorthWest()
        {
            return "frts.vanillasdl2.command.movescreen.northwest";
        }

        static std::string moveScreenCommandNorthEast()
        {
            return "frts.vanillasdl2.command.movescreen.northeast";
        }

        static std::string moveScreenCommandSouthWest()
        {
            return "frts.vanillasdl2.command.movescreen.southwest";
        }

        static std::string moveScreenCommandSouthEast()
        {
            return "frts.vanillasdl2.command.movescreen.southeast";
        }

        static std::string moveScreenCommandUp()
        {
            return "frts.vanillasdl2.command.movescreen.up";
        }

        static std::string moveScreenCommandDown()
        {
            return "frts.vanillasdl2.command.movescreen.down";
        }

        static std::string moveCursorCommandWest()
        {
            return "frts.vanillasdl2.command.movecursor.west";
        }

        static std::string moveCursorCommandEast()
        {
            return "frts.vanillasdl2.command.movecursor.east";
        }

        static std::string moveCursorCommandNorth()
        {
            return "frts.vanillasdl2.command.movecursor.north";
        }

        static std::string moveCursorCommandSouth()
        {
            return "frts.vanillasdl2.command.movecursor.south";
        }

        static std::string moveCursorCommandNorthWest()
        {
            return "frts.vanillasdl2.command.movecursor.northwest";
        }

        static std::string moveCursorCommandNorthEast()
        {
            return "frts.vanillasdl2.command.movecursor.northeast";
        }

        static std::string moveCursorCommandSouthWest()
        {
            return "frts.vanillasdl2.command.movecursor.southwest";
        }

        static std::string moveCursorCommandSouthEast()
        {
            return "frts.vanillasdl2.command.movecursor.southeast";
        }

        static std::string renderable()
        {
            return "frts.vanillasdl2.entity.component.renderable";
        }
    };
}

#endif // FRTS_SDL2IDS_H
