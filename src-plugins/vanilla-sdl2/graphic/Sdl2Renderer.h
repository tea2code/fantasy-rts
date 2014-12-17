#ifndef FRTS_SDL2RENDERER_H
#define FRTS_SDL2RENDERER_H

#include "impl/Drawer.h"
#include "impl/FpsManager.h"

#include <frts/BaseTickable.h>

#include <memory>
#include <string>


namespace frts
{
    class Sdl2Renderer : public BaseTickable
    {
    public:
        Sdl2Renderer();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/SDL2Renderer";
        }

        void checkRequiredData(SharedManagerPtr shared) override;
        bool createData(SharedManagerPtr shared) override;
        std::vector<std::string> getSupportedConfig() override;
        bool init(SharedManagerPtr shared) override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        void tick(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

    private:
        std::string cursorId;
        Drawer drawer;
        bool firstInit = true;
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
