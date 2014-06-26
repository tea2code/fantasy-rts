#ifndef FRTS_EVENTHANDLER_H
#define FRTS_EVENTHANDLER_H

#include "Key.h"

#include <frts/module>
#include <frts/vanillacommand>


namespace frts
{
    /**
     * @brief The event handler consumes the SDL2 event queue and handles all
     *        events but mostly input events.
     */
    class EventHandler : public Tickable
    {
    public:
        virtual ~EventHandler() {}

        /**
         * @brief Register a custom command with an key.
         * @param key The key.
         * @param command The command.
         */
        virtual void registerCommand(Key key, CommandPtr command) = 0;
    };
}

#endif // FRTS_EVENTHANDLER_H
