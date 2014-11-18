#ifndef FRTS_EVENTHANDLER_H
#define FRTS_EVENTHANDLER_H

#include <frts/BaseTickable.h>

#include <SDL2/SDL.h>

#include <unordered_map>
#include <memory>


namespace frts
{
    class EventHandler;

    /**
     * @brief Pointer to EventHandler.
     */
    using EventHandlerPtr = std::shared_ptr<EventHandler>;

    class EventHandler : public BaseTickable
    {
    public:
        EventHandler();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/EventHandler";
        }

        void tick(SharedManagerPtr shared) override;

        /**
         * @brief Register a custom command with an key.
         * @param key The key.
         * @param commandId The command id.
         */
        void registerCommand(SDL_Keycode key, IdPtr commandId);

    private:
        std::unordered_map<SDL_Keycode, IdPtr, std::hash<char>> keyCommands;
    };

    /**
     * @brief Create new EventHandler.
     * @return The module.
     */
    inline EventHandlerPtr makeEventHandler()
    {
        return std::make_shared<EventHandler>();
    }
}

#endif // FRTS_EVENTHANDLER_H
