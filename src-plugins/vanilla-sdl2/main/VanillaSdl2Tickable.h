#ifndef FRTS_VANILLASDL2TICKABLE_H
#define FRTS_VANILLASDL2TICKABLE_H

#include <frts/module>

#include <SDL2/SDL.h>


namespace frts
{
    /**
     * @brief Temporary test module.
     */
    class VanillaSdl2Tickable : public Tickable
    {
    public:
        VanillaSdl2Tickable();
        ~VanillaSdl2Tickable();

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
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Window *window;

        unsigned int lastTime;
    };
}

#endif // FRTS_VANILLASDL2TICKABLE_H
