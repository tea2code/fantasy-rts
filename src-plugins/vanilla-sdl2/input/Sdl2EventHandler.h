#ifndef FRTS_SDL2Sdl2EventHandler_H
#define FRTS_SDL2Sdl2EventHandler_H

#include <frts/BaseTickable.h>

#include <SDL2/SDL.h>

#include <stack>
#include <unordered_map>
#include <memory>


namespace frts
{
    /**
     * @brief Simple struct for a key command consisting of a key and optional modifiers.
     */
    struct Sdl2KeyCommand
    {
        Sdl2KeyCommand(SDL_Keycode key,
                       bool alt = false, bool ctrl = false, bool shift = false,
                       IdPtr context = nullptr)
            : key{key}, alt{alt}, ctrl{ctrl}, shift{shift}, context{context}
        {}

        SDL_Keycode key;

        bool alt;
        bool ctrl;
        bool shift;

        IdPtr context;

        bool operator==(const Sdl2KeyCommand &other) const
        {
            return (key == other.key) &&
                   (alt == other.alt) &&
                   (ctrl == other.ctrl) &&
                   (shift == other.shift) &&
                   (context == other.context);
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
            result = 31 * result + std::hash<frts::IdPtr>()(keyCommand.context);
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

        /**
         * @brief Register a context change with an key.
         * @param keyCommand The key command.
         * @param context The context:
         */
        void registerContextChange(Sdl2KeyCommand keyCommand, IdPtr context);

        /**
         * @brief Set the default context.
         * @param context The default context.
         */
        void setDefaultContext(IdPtr context);

    private:
        /**
         * @brief A key command could be a real command or a context change.
         */
        struct CommandContextChange
        {
            IdPtr command;
            IdPtr contextChange;
        };

    private:
        std::stack<IdPtr> contextStack;
        IdPtr defaultContext;
        std::unordered_map<Sdl2KeyCommand, CommandContextChange> keyCommands;
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
