#ifndef FRTS_SDL2Sdl2EventHandler_H
#define FRTS_SDL2Sdl2EventHandler_H

#include <frts/BaseTickable.h>

#include <SDL2/SDL.h>

#include <unordered_map>
#include <memory>


namespace frts
{
    /**
     * @brief Simple struct for a key command consisting of a key and optional modifiers.
     */
    struct Sdl2KeyCommand
    {
        Sdl2KeyCommand(SDL_Keycode key, bool alt = false, bool ctrl = false, bool shift = false)
            : key{key}, alt{alt}, ctrl{ctrl}, shift{shift}
        {}

        SDL_Keycode key;

        bool alt;
        bool ctrl;
        bool shift;

        bool operator==(const Sdl2KeyCommand &other) const
        {
            return (key == other.key) &&
                   (alt == other.alt) &&
                   (ctrl == other.ctrl) &&
                   (shift == other.shift);
        }
    };
}

namespace std
{
    /**
     * @brief Hash for key commands.
     */
    template <>
    struct hash<frts::Sdl2KeyCommand>
    {
        size_t operator()(const frts::Sdl2KeyCommand& keyCommand) const
        {
            size_t result = 17;
            result = 31 * result + std::hash<char>()(static_cast<char>(keyCommand.key));
            result = 31 * result + std::hash<bool>()(keyCommand.alt);
            result = 31 * result + std::hash<bool>()(keyCommand.ctrl);
            result = 31 * result + std::hash<bool>()(keyCommand.shift);
            return result;
        }
    };
}

namespace frts
{
    class Sdl2EventHandler;

    /**
     * @brief Pointer to Sdl2EventHandler.
     */
    using Sdl2EventHandlerPtr = std::shared_ptr<Sdl2EventHandler>;

    class Sdl2EventHandler : public BaseTickable
    {
    public:
        Sdl2EventHandler();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/SDL2EventHandler";
        }

        void checkRequiredData(SharedManagerPtr shared) override;
        bool createData(SharedManagerPtr shared) override;
        std::vector<std::string> getSupportedConfig() override;
        bool init(SharedManagerPtr shared) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        /**
         * @brief Register a custom command with an key.
         * @param keyCommand The key command.
         * @param commandId The command id.
         */
        void registerCommand(Sdl2KeyCommand keyCommand, IdPtr commandId);

    private:
        std::unordered_map<Sdl2KeyCommand, IdPtr> keyCommands;
    };

    /**
     * @brief Create new Sdl2EventHandler.
     * @return The module.
     */
    inline Sdl2EventHandlerPtr makeSdl2EventHandler()
    {
        return std::make_shared<Sdl2EventHandler>();
    }
}

#endif // FRTS_SDL2Sdl2EventHandler_H
