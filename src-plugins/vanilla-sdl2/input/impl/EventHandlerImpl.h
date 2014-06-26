#ifndef FRTS_EVENTHANDLERIMPL_H
#define FRTS_EVENTHANDLERIMPL_H

#include <input/EventHandler.h>

#include <SDL2/SDL.h>

#include <unordered_map>
#include <memory>


namespace frts
{
    class EventHandlerImpl : public EventHandler
    {
    public:
        EventHandlerImpl();

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

        std::vector<ConfigNodePtr> configNodes;
        bool firstInit = true;
        std::unordered_map<SDL_Keycode, CommandPtr, std::hash<char>> keyCommands;
    };

    /**
     * @brief Create new EventHandler.
     * @return The module.
     */
    inline ModulePtr makeEventHandler()
    {
        return std::make_shared<EventHandlerImpl>();
    }
}

#endif // FRTS_EVENTHANDLERIMPL_H
