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
        /**
         * @brief Simple struct for a key command consisting of a key and optional modifiers.
         */
        struct KeyCommand
        {
            KeyCommand(Key key, bool alt = false, bool ctrl = false, bool shift = false)
                : key{key}, alt{alt}, ctrl{ctrl}, shift{shift}
            {}

            Key key;

            bool alt;
            bool ctrl;
            bool shift;
        };

    public:
        virtual ~InputHandler() {}

        /**
         * @brief Register a custom command with an key.
         * @param keyCommand The key command.
         * @param commandId The command id.
         */
        virtual void registerCommand(KeyCommand keyCommand, IdPtr commandId) = 0;
    };
}

#endif // FRTS_INPUTHANDLER_H
