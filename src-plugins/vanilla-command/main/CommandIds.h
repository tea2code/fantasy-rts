#ifndef FRTS_COMMANDIDS_H
#define FRTS_COMMANDIDS_H

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of command ID strings.
     */
    class CommandIds
    {
    public:
        static std::string commandConfig()
        {
            return "frts::CommandConfig";
        }

        static std::string commandFactory()
        {
            return "frts::CommandFactory";
        }

        static std::string quit()
        {
            return "frts.vanillacommand.command.quit";
        }

        static std::string undo()
        {
            return "frts.vanillacommand.command.undo";
        }
    };
}

#endif // FRTS_COMMANDIDS_H
