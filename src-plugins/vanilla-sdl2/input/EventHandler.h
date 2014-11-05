#ifndef FRTS_EVENTHANDLER_H
#define FRTS_EVENTHANDLER_H

#include <frts/module>
#include <frts/vanillacommand>

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

    class EventHandler : public Tickable
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

        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        /**
         * @brief Register a custom command with an key.
         * @param key The key.
         * @param command The command.
         */
        void registerCommand(SDL_Keycode key, CommandPtr command);

    private:
        std::unordered_map<SDL_Keycode, CommandPtr, std::hash<char>> keyCommands;
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
