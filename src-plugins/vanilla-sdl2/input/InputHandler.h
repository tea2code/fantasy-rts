#ifndef FRTS_INPUTHANDLER_H
#define FTS_INPUTHANDLER_H

#include "Key.h"

#include <frts/module>
#include <frts/vanillacommand>


namespace frts
{
    /**
     * @brief The input handler allows to register commands to certain keys.
     */
    class InputHandler : public Utility
    {
    public:
        virtual ~InputHandler() {}

        /**
         * @brief Register a custom command with an key.
         * @param key The key.
         * @param command The command.
         */
        virtual void registerCommand(Key key, CommandPtr command) = 0;
    };
}

#endif // FRTS_INPUTHANDLER_H
