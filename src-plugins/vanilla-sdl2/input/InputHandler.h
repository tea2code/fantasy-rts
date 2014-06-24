#ifndef FRTS_INPUTHANDLER_H
#define FRTS_INPUTHANDLER_H

#include "Key.h"

#include <frts/module>
#include <frts/vanillacommand>


namespace frts
{
    /**
     * @brief The input handler consumes the SDL2 event queue and handles all
     *        input events.
     */
    class InputHandler : public Tickable
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
