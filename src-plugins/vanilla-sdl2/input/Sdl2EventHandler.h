#ifndef FRTS_SDL2Sdl2EventHandler_H
#define FRTS_SDL2Sdl2EventHandler_H

#include <frts/BaseTickable.h>
#include <frts/shared>

#include <SDL2/SDL.h>

#include <cstdint>
#include <stack>
#include <unordered_map>
#include <memory>


namespace frts
{
    /**
     * @brief Simple struct for a key command consisting of a key and optional modifiers.
     */
    template <typename ButtonType>
    struct Sdl2ButtonCommand
    {
        Sdl2ButtonCommand(ButtonType button,
                       bool alt = false, bool ctrl = false, bool shift = false,
                       const IdPtr& context = nullptr)
            : button{button}, alt{alt}, ctrl{ctrl}, shift{shift}, context{context}
        {}

        ButtonType button;

        bool alt;
        bool ctrl;
        bool shift;

        IdPtr context;

        bool operator==(const Sdl2ButtonCommand<ButtonType>& other) const
        {
            return (button == other.button) &&
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
    template <typename ButtonType>
    struct hash<frts::Sdl2ButtonCommand<ButtonType>>
    {
        size_t operator()(const frts::Sdl2ButtonCommand<ButtonType>& buttonCommand) const
        {
            size_t result = 17;
            result = 31 * result + std::hash<ButtonType>()(buttonCommand.button);
            result = 31 * result + std::hash<bool>()(buttonCommand.alt);
            result = 31 * result + std::hash<bool>()(buttonCommand.ctrl);
            result = 31 * result + std::hash<bool>()(buttonCommand.shift);
            result = 31 * result + std::hash<frts::IdPtr>()(buttonCommand.context);
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

    class Sdl2EventHandler : public BaseTickable<Tickable>
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

        void checkRequiredData(const SharedManagerPtr& shared) override;
        bool createData(const SharedManagerPtr& shared) override;
        std::vector<std::string> getSupportedConfig() override;
        bool init(const SharedManagerPtr& shared) override;
        void parseConfig(const std::string& key, const ConfigNodePtr& node, const SharedManagerPtr& shared) override;
        void tick(const SharedManagerPtr& shared) override;
        void validateModules(const SharedManagerPtr& shared) override;

        /**
         * @brief Closes the current context.
         * @param resetToDefault If true all contexts are closed else only the current.
         */
        void closeContext(bool resetToDefault = false);

        /**
         * @brief Register a custom command with an key.
         * @param keyCommand The key command.
         * @param commandId The command id.
         */
        void registerCommand(const Sdl2ButtonCommand<SDL_Keycode>& keyCommand, const IdPtr& commandId);

        /**
         * @brief Register a custom command with an mouse button.
         * @param mouseButtonCommand The mouse button command.
         * @param commandId The command id.
         */
        void registerCommand(const Sdl2ButtonCommand<std::uint8_t>& mouseButtonCommand, const IdPtr& commandId);

        /**
         * @brief Register a context change with an key.
         * @param keyCommand The key command.
         * @param context The context:
         */
        void registerContextChange(const Sdl2ButtonCommand<SDL_Keycode>& keyCommand, const IdPtr& context);

        /**
         * @brief Register a context change with an mouse button.
         * @param mouseButtonCommand The mouse button command.
         * @param context The context:
         */
        void registerContextChange(const Sdl2ButtonCommand<std::uint8_t>& mouseButtonCommand, const IdPtr& context);

        /**
         * @brief Set the default context.
         * @param context The default context.
         */
        void setDefaultContext(const IdPtr& context);

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
        std::unordered_map<Sdl2ButtonCommand<SDL_Keycode>, CommandContextChange> keyCommands;
        std::unordered_map<Sdl2ButtonCommand<std::uint8_t>, CommandContextChange> mouseButtonsCommands;

    private:
        void executeCommandContextChange(const CommandContextChange& ccc, const SharedManagerPtr& shared);
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
