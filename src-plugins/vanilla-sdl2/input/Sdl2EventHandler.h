#ifndef FRTS_SDL2Sdl2EventHandler_H
#define FRTS_SDL2Sdl2EventHandler_H

#include <frts/BaseTickable.h>

#include <SDL2/SDL.h>

#include <unordered_map>
#include <memory>


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
            return "frts/Sdl2EventHandler";
        }

        void checkRequiredData(SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

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
     * @brief Create new Sdl2EventHandler.
     * @return The module.
     */
    inline Sdl2EventHandlerPtr makeSdl2EventHandler()
    {
        return std::make_shared<Sdl2EventHandler>();
    }
}

#endif // FRTS_SDL2Sdl2EventHandler_H
