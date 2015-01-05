#ifndef FRTS_ACTIONIDS
#define FRTS_ACTIONIDS

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of action ID strings.
     */
    class ActionIds
    {
    public:
        static std::string actionManager()
        {
            return "frts::ActionManager";
        }

        static std::string stopActionCommand()
        {
            return "frts.vanillaaction.command.stopaction";
        }

        static std::string stopActionOrQuitCommand()
        {
            return "frts.vanillaaction.command.stopactionorquit";
        }
    };
}

#endif // FRTS_ACTIONIDS

