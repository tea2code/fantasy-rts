#ifndef FRTS_INPUTHANDLERIMPL_H
#define FRTS_INPUTHANDLERIMPL_H

#include <input/EventHandler.h>
#include <input/InputHandler.h>

#include <SDL2/SDL.h>

#include <memory>


namespace frts
{
    class InputHandlerImpl : public InputHandler
    {
    public:
        /**
         * @param eventHandler The event handler.
         */
        InputHandlerImpl(EventHandlerPtr eventHandler);

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
        void registerCommand(Key key, IdPtr commandId) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        std::vector<ConfigNodePtr> configNodes;
        EventHandlerPtr eventHandler;
        bool firstInit = true;
    };

    /**
     * @brief Create new InputHandler.
     * @param eventHandler The event handler.
     * @return The module.
     */
    inline ModulePtr makeInputHandler(EventHandlerPtr eventHandler)
    {
        assert(eventHandler != nullptr);

        return std::make_shared<InputHandlerImpl>(eventHandler);
    }
}

#endif // FRTS_INPUTHANDLERIMPL_H
