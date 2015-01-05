#ifndef FRTS_VANILLASDL2PLUGIN_H
#define FRTS_VANILLASDL2PLUGIN_H

#include <input/Sdl2EventHandler.h>

#include <frts/plugin>

#include <string>


namespace frts
{
    class VanillaSdl2Plugin : public Plugin
    {
    public:
        VanillaSdl2Plugin();

        ModulePtr getModule(frts::IdPtr id) override;

    private:
        Sdl2EventHandlerPtr sdl2EventHandler;

    private:
        Sdl2EventHandlerPtr getSdl2EventHandler();
    };
}

#endif // FRTS_VANILLASDL2PLUGIN_H
