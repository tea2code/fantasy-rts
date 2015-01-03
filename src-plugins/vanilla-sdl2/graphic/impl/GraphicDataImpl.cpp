#include "GraphicDataImpl.h"

#include <main/Sdl2Ids.h>


frts::GraphicDataImpl::GraphicDataImpl()
{}

frts::EntityPtr frts::GraphicDataImpl::getCursor() const
{
    return cursor;
}

frts::GraphicData::ScreenArea frts::GraphicDataImpl::getMapArea() const
{
    return mapArea;
}

unsigned int frts::GraphicDataImpl::getNumFpsAvg() const
{
    return numFpsAvg;
}

std::string frts::GraphicDataImpl::getName() const
{
    return Sdl2Ids::graphicData();
}

frts::GraphicData::pixel frts::GraphicDataImpl::getScreenHeight() const
{
    return screenHeight;
}

frts::GraphicData::pixel frts::GraphicDataImpl::getScreenOffsetStepX() const
{
    return screenOffsetStepX;
}

frts::GraphicData::pixel frts::GraphicDataImpl::getScreenOffsetStepY() const
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

frts::GraphicData::pixel frts::GraphicDataImpl::getScreenWidth() const
{
    return screenWidth;
}

frts::GraphicData::ScreenArea frts::GraphicDataImpl::getSidebarArea() const
{
    return sidebarArea;
}

int frts::GraphicDataImpl::getSidebarInfoIndex() const
{
    return sidebarInfoIndex;
}

frts::GraphicData::pixel frts::GraphicDataImpl::getSidebarWidth() const
{
    return sidebarWidth;
}

frts::GraphicData::pixel frts::GraphicDataImpl::getTileHeight() const
{
    return tileHeight;
}

frts::GraphicData::pixel frts::GraphicDataImpl::getTileWidth() const
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
    return 4;
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

void frts::GraphicDataImpl::setMapArea(ScreenArea mapArea)
{
    this->mapArea = mapArea;
}

void frts::GraphicDataImpl::setNumFpsAvg(unsigned int numFpsAvg)
{
    this->numFpsAvg = numFpsAvg;
}

void frts::GraphicDataImpl::setRenderEverything(bool renderEverything)
{
    this->renderEverything = renderEverything;
}

void frts::GraphicDataImpl::setScreenHeight(frts::GraphicData::pixel screenHeight)
{
    this->screenHeight = screenHeight;
}

void frts::GraphicDataImpl::setScreenOffsetStepX(frts::GraphicData::pixel offsetStep)
{
    this->screenOffsetStepX = offsetStep;
}

void frts::GraphicDataImpl::setScreenOffsetStepY(frts::GraphicData::pixel offsetStep)
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

void frts::GraphicDataImpl::setScreenWidth(frts::GraphicData::pixel screenWidth)
{
    this->screenWidth = screenWidth;
}

void frts::GraphicDataImpl::setSidebarArea(ScreenArea sidebarArea)
{
    this->sidebarArea = sidebarArea;
}

void frts::GraphicDataImpl::setSidebarInfoIndex(int index)
{
    this->sidebarInfoIndex = index;
}

void frts::GraphicDataImpl::setSidebarWidth(frts::GraphicData::pixel sidebarWidth)
{
    this->sidebarWidth = sidebarWidth;
}

void frts::GraphicDataImpl::setTileHeight(frts::GraphicData::pixel tileHeight)
{
    this->tileHeight = tileHeight;
}

void frts::GraphicDataImpl::setTileWidth(frts::GraphicData::pixel tileWidth)
{
    this->tileWidth = tileWidth;
}

void frts::GraphicDataImpl::setZLevel(Point::value zLevel)
{
    this->zLevel = zLevel;
}
