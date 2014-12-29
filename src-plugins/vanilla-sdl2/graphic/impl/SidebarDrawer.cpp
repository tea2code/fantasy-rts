#include "SidebarDrawer.h"

#include <main/Sdl2Ids.h>


frts::SidebarDrawer::SidebarDrawer()
{

}

frts::SidebarDrawer::~SidebarDrawer()
{
    renderer.reset();
}

void frts::SidebarDrawer::drawRectangle(GraphicData::Pixel x, GraphicData::Pixel y, GraphicData::Pixel width, GraphicData::Pixel height,
                                        std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    SDL_Rect rectToRender = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)
    };
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, 0);
    SDL_RenderFillRect(renderer.get(), &rectToRender);
}

void frts::SidebarDrawer::init(Drawer::RendererPtr renderer, SharedManagerPtr)
{
    assert(renderer != nullptr);

    this->renderer = renderer;
    initialized = true;
}

void frts::SidebarDrawer::setSidebarConfig(SharedManagerPtr shared, ConfigNodePtr sidebarNode)
{
    assert(shared != nullptr);
    assert(sidebarNode != nullptr);

    if (sidebarNode->has("background"))
    {
        auto rgbNode = sidebarNode->getNode("background");
        backgroundR = rgbNode->getInteger("r");
        backgroundG = rgbNode->getInteger("g");
        backgroundB = rgbNode->getInteger("b");
    }

    if (sidebarNode->has("font-color"))
    {
        auto rgbNode = sidebarNode->getNode("font-color");
        fontColor.r = rgbNode->getInteger("r");
        fontColor.g = rgbNode->getInteger("g");
        fontColor.b = rgbNode->getInteger("b");
    }

    if (sidebarNode->has("line-color"))
    {
        auto rgbNode = sidebarNode->getNode("line-color");
        lineColorR = rgbNode->getInteger("r");
        lineColorG = rgbNode->getInteger("g");
        lineColorB = rgbNode->getInteger("b");
    }

    if (sidebarNode->has("tile-background"))
    {
        auto rgbNode = sidebarNode->getNode("tile-background");
        tileBackgroundR = rgbNode->getInteger("r");
        tileBackgroundG = rgbNode->getInteger("g");
        tileBackgroundB = rgbNode->getInteger("b");
    }
}

void frts::SidebarDrawer::updateEvents(std::vector<IdPtr> events, SharedManagerPtr shared)
{
    assert(initialized);
    assert(shared != nullptr);

    // TODO
}

void frts::SidebarDrawer::updateInfo(SharedManagerPtr shared)
{
    assert(initialized);
    assert(shared != nullptr);

    // TODO
}

void frts::SidebarDrawer::updateSidebar(std::vector<IdPtr> events, SharedManagerPtr shared)
{
    assert(initialized);
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto area = gd->getSidebarArea();

    // Draw background.
    drawRectangle(area.x, area.y, area.width, area.height, backgroundR, backgroundG, backgroundB);

    // Draw info.
    updateInfo(shared);

    // Draw events.
    updateEvents(events, shared);
}


void frts::SidebarDrawer::validateData(SharedManagerPtr)
{
    // Everything is ok.
}
