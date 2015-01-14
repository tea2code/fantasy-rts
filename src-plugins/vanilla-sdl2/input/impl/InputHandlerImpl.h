#ifndef FRTS_INPUTHANDLERIMPL_H
#define FRTS_INPUTHANDLERIMPL_H

#include <input/Sdl2EventHandler.h>
#include <input/InputHandler.h>

#include <SDL2/SDL.h>

#include <memory>


namespace frts
{
    class InputHandlerImpl : public InputHandler
    {
    public:
        /**
         * @param sdl2EventHandler The event handler.
         */
        InputHandlerImpl(Sdl2EventHandlerPtr sdl2EventHandler);

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/InputHandler";
        }

        void checkRequiredData(SharedManagerPtr shared) override;
        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        bool isInitialized() const override;
        bool isPreInitialized() const override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        void closeCurrentContext() override;
        void registerCommand(KeyCommand keyCommand, IdPtr commandId) override;
        void registerContextChange(KeyCommand keyCommand, IdPtr context) override;

    private:
        std::vector<ConfigNodePtr> configNodes;
        Sdl2EventHandlerPtr sdl2EventHandler;

        bool isInit = false;
        bool isPreInit = false;
    };

    /**
     * @brief Create new InputHandler.
     * @param sdl2EventHandler The event handler.
     * @return The module.
     */
    inline ModulePtr makeInputHandler(Sdl2EventHandlerPtr sdl2EventHandler)
    {
        assert(sdl2EventHandler != nullptr);

        return std::make_shared<InputHandlerImpl>(sdl2EventHandler);
    }
}

#endif // FRTS_INPUTHANDLERIMPL_H
