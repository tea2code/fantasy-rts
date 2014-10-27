#include "Sdl2Renderer.h"

#include "Drawer.h"
#include "FpsManager.h"


bool frts::Sdl2Renderer::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::Sdl2Renderer::getName() const
{
    return "frts::Sdl2Renderer";
}

std::vector<std::string> frts::Sdl2Renderer::getSupportedConfig()
{
    return {};
}

int frts::Sdl2Renderer::getVersion() const
{
    return 1;
}

bool frts::Sdl2Renderer::init(SharedManagerPtr)
{
    return false;
}

void frts::Sdl2Renderer::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::Sdl2Renderer::preInit(SharedManagerPtr)
{
    return false;
}

void frts::Sdl2Renderer::tick(SharedManagerPtr)
{

}

void frts::Sdl2Renderer::validateData(SharedManagerPtr)
{
    // MainData
}

void frts::Sdl2Renderer::validateModules(SharedManagerPtr)
{
    // VanillaModel
}
