#include "GraphicDataImpl.h"

#include <main/Sdl2Ids.h>


frts::GraphicDataImpl::GraphicDataImpl()
{}

frts::EntityPtr frts::GraphicDataImpl::getCursor() const
{
    return cursor;
}

frts::GraphicData::ScreenArea frts::GraphicDataImpl::getmapArea() const
{
    return mapArea;
}

unsigned int frts::GraphicDataImpl::getMaxFps() const
{
    return maxFps;
}

unsigned int frts::GraphicDataImpl::getNumFpsAvg() const
{
    return numFpsAvg;
}

std::string frts::GraphicDataImpl::getName() const
{
    return Sdl2Ids::graphicData();
}

frts::GraphicData::Pixel frts::GraphicDataImpl::getScreenHeight() const
{
    return screenHeight;
}

frts::GraphicData::Pixel frts::GraphicDataImpl::getScreenOffsetStepX() const
{
    return screenOffsetStepX;
}

frts::GraphicData::Pixel frts::GraphicDataImpl::getScreenOffsetStepY() const
{
    return screenOffsetStepY;
}

frts::Point::value frts::GraphicDataImpl::getScreenOffsetX() const
{
    return screenOffsetX;
}

frts::Point::value frts::GraphicDataImpl::getScreenOffsetY() const
{
    return screenOffsetY;
}

std::string frts::GraphicDataImpl::getScreenTitle() const
{
    return screenTitle;
}

frts::GraphicData::Pixel frts::GraphicDataImpl::getScreenWidth() const
{
    return screenWidth;
}

frts::GraphicData::ScreenArea frts::GraphicDataImpl::getsidebarArea() const
{
    return sidebarArea;
}

frts::GraphicData::Pixel frts::GraphicDataImpl::getSidebarWidth() const
{
    return sidebarWidth;
}

frts::GraphicData::Pixel frts::GraphicDataImpl::getTileHeight() const
{
    return tileHeight;
}

frts::GraphicData::Pixel frts::GraphicDataImpl::getTileWidth() const
{
    return tileWidth;
}

std::string frts::GraphicDataImpl::getTypeName() const
{
    return getName();
}

int frts::GraphicDataImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::GraphicDataImpl::getVersion() const
{
    return 2;
}

frts::Point::value frts::GraphicDataImpl::getZLevel() const
{
    return zLevel;
}

bool frts::GraphicDataImpl::isRenderEverything() const
{
    return renderEverything;
}

void frts::GraphicDataImpl::setCursor(EntityPtr cursor)
{
    this->cursor = cursor;
}

void frts::GraphicDataImpl::setmapArea(ScreenArea mapArea)
{
    this->mapArea = mapArea;
}

void frts::GraphicDataImpl::setMaxFps(unsigned int maxFps)
{
    this->maxFps = maxFps;
}

void frts::GraphicDataImpl::setNumFpsAvg(unsigned int numFpsAvg)
{
    this->numFpsAvg = numFpsAvg;
}

void frts::GraphicDataImpl::setRenderEverything(bool renderEverything)
{
    this->renderEverything = renderEverything;
}

void frts::GraphicDataImpl::setScreenHeight(frts::GraphicData::Pixel screenHeight)
{
    this->screenHeight = screenHeight;
}

void frts::GraphicDataImpl::setScreenOffsetStepX(frts::GraphicData::Pixel offsetStep)
{
    this->screenOffsetStepX = offsetStep;
}

void frts::GraphicDataImpl::setScreenOffsetStepY(frts::GraphicData::Pixel offsetStep)
{
    this->screenOffsetStepY = offsetStep;
}

void frts::GraphicDataImpl::setScreenOffsetX(Point::value offset)
{
    this->screenOffsetX = offset;
}

void frts::GraphicDataImpl::setScreenOffsetY(Point::value offset)
{
    this->screenOffsetY = offset;
}

void frts::GraphicDataImpl::setScreenTitle(const std::string& screenTitle)
{
    this->screenTitle = screenTitle;
}

void frts::GraphicDataImpl::setScreenWidth(frts::GraphicData::Pixel screenWidth)
{
    this->screenWidth = screenWidth;
}

void frts::GraphicDataImpl::setsidebarArea(ScreenArea sidebarArea)
{
    this->sidebarArea = sidebarArea;
}

void frts::GraphicDataImpl::setSidebarWidth(frts::GraphicData::Pixel sidebarWidth)
{
    this->sidebarWidth = sidebarWidth;
}

void frts::GraphicDataImpl::setTileHeight(frts::GraphicData::Pixel tileHeight)
{
    this->tileHeight = tileHeight;
}

void frts::GraphicDataImpl::setTileWidth(frts::GraphicData::Pixel tileWidth)
{
    this->tileWidth = tileWidth;
}

void frts::GraphicDataImpl::setZLevel(Point::value zLevel)
{
    this->zLevel = zLevel;
}
