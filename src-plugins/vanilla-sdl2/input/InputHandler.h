#ifndef FRTS_INPUTHANDLER_H
#define FTS_INPUTHANDLER_H

#include "Key.h"
#include "MouseButton.h"

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
         * @brief Simple struct for a button command consisting of a key and optional modifiers.
         */
        template <typename ButtonType>
        struct ButtonCommand
        {
            ButtonCommand(ButtonType button, bool alt = false, bool ctrl = false, bool shift = false, const IdPtr& context = nullptr)
                : button{button}, alt{alt}, ctrl{ctrl}, shift{shift}, context{context}
            {}

            ButtonType button;

            bool alt;
            bool ctrl;
            bool shift;

            IdPtr context;
        };

    public:
        virtual ~InputHandler() {}

        /**
         * @brief Closes the current context.
         * @param resetToDefault If true all contexts are closed else only the current.
         */
        virtual void closeContext(bool resetToDefault = false) = 0;

        /**
         * @brief Register a custom command with an key.
         * @param keyCommand The key command.
         * @param commandId The command id.
         */
        virtual void registerCommand(const ButtonCommand<Key>& keyCommand, const IdPtr& commandId) = 0;

        /**
         * @brief Register a custom command with an mouse button.
         * @param mouseButtonCommand The mouse button command.
         * @param commandId The command id.
         */
        virtual void registerCommand(const ButtonCommand<MouseButton>& mouseButtonCommand, const IdPtr& commandId) = 0;

        /**
         * @brief Register a context change with an key.
         * @param keyCommand The key command.
         * @param context The context:
         */
        virtual void registerContextChange(const ButtonCommand<Key>& keyCommand, const IdPtr& context) = 0;

        /**
         * @brief Register a context change with an mouse button.
         * @param mouseButtonCommand The mouse button command.
         * @param context The context:
         */
        virtual void registerContextChange(const ButtonCommand<MouseButton>& mouseButtonCommand, const IdPtr& context) = 0;
    };
}

#endif // FRTS_INPUTHANDLER_H
