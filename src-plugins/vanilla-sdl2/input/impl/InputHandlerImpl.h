#ifndef FRTS_INPUTHANDLERIMPL_H
#define FRTS_INPUTHANDLERIMPL_H

#include <input/Sdl2EventHandler.h>
#include <input/InputHandler.h>
#include <frts/BaseUtility.h>

#include <SDL2/SDL.h>

#include <memory>


namespace frts
{
    class InputHandlerImpl : public BaseUtility<InputHandler>
    {
    public:
        /**
         * @param sdl2EventHandler The event handler.
         */
        InputHandlerImpl(const Sdl2EventHandlerPtr& sdl2EventHandler);

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/InputHandler";
        }

        std::vector<std::string> getSupportedConfig() override;
        bool init(const SharedManagerPtr& shared) override;
        void parseConfig(const std::string& key, const ConfigNodePtr& node, const SharedManagerPtr& shared) override;
        void validateModules(const SharedManagerPtr& shared) override;

        void closeCurrentContext() override;
        void registerCommand(const ButtonCommand<Key>& keyCommand, const IdPtr& commandId) override;
        void registerCommand(const ButtonCommand<MouseButton>& mouseButtonCommand, const IdPtr& commandId) override;
        void registerContextChange(const ButtonCommand<Key>& keyCommand, const IdPtr& context) override;
        void registerContextChange(const ButtonCommand<MouseButton>& mouseButtonCommand, const IdPtr& context) override;

    private:
        std::vector<ConfigNodePtr> configNodes;
        Sdl2EventHandlerPtr sdl2EventHandler;
    };

    /**
     * @brief Create new InputHandler.
     * @param sdl2EventHandler The event handler.
     * @return The module.
     */
    inline ModulePtr makeInputHandler(const Sdl2EventHandlerPtr& sdl2EventHandler)
    {
        assert(sdl2EventHandler != nullptr);

        return std::make_shared<InputHandlerImpl>(sdl2EventHandler);
    }
}

#endif // FRTS_INPUTHANDLERIMPL_H
