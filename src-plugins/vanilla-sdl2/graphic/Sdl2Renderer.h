#ifndef FRTS_SDL2RENDERER_H
#define FRTS_SDL2RENDERER_H

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
