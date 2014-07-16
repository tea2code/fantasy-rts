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
        virtual ~Sdl2Renderer() {}

        /**
         * @brief Set the fps manager. Must be called before init() or else
         *        the behaviour is undefined.
         * @param manager The fps manager.
         */
        virtual void setFpsManager(FpsManager manager) = 0;

        /**
         * @brief Set the drawer. Must be called before init() or else
         *        the behaviour is undefined.
         * @param drawer The drawer.
         */
        virtual void setDrawer(Drawer drawer) = 0;
    };
}

#endif // FRTS_SDL2RENDERER_H
