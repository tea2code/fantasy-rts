#ifndef FRTS_SDL2RENDERER_H
#define FRTS_SDL2RENDERER_H

#include "Drawer.h"
#include "FpsManager.h"

#include <frts/module>

#include <memory>


namespace frts
{
    class Sdl2Renderer : public Tickable
    {
    public:
        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        Drawer drawer;
        FpsManager fpsManager;

    private:
        /**
         * @brief Retrieves the graphic data.
         * @param shared The shared manager.
         * @return The graphic data.
         */
        GraphicDataPtr graphicData(SharedManagerPtr shared) const;
    };

    /**
     * @brief Create new Sdl2Renderer.
     * @return The Sdl2Renderer.
     */
    inline TickablePtr makeSdl2Renderer()
    {
        return std::make_shared<Sdl2Renderer>();
    }
}

#endif // FRTS_SDL2RENDERER_H
