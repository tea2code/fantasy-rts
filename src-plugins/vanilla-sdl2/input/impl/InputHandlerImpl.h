#ifndef FRTS_INPUTHANDLERIMPL_H
#define FRTS_INPUTHANDLERIMPL_H

#include <input/InputHandler.h>

#include <SDL2/SDL.h>

#include <unordered_map>
#include <memory>


namespace frts
{
    class InputHandlerImpl : public InputHandler
    {
    public:
        InputHandlerImpl();

        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        void registerCommand(Key key, CommandPtr command) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        const std::string configKey = "keys";

        std::unordered_map<SDL_Keycode, CommandPtr, std::hash<char>> keyCommands;
    };

    /**
     * @brief Create new InputHandler.
     * @return The module.
     */
    inline ModulePtr makeInputHandler()
    {
        return std::make_shared<InputHandlerImpl>();
    }
}

#endif // FRTS_INPUTHANDLERIMPL_H
