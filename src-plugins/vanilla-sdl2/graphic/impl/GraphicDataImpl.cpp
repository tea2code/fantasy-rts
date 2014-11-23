#include "GraphicDataImpl.h"

#include <main/Sdl2Ids.h>


frts::EntityPtr frts::GraphicDataImpl::getCursor() const
{
    return cursor;
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

unsigned int frts::GraphicDataImpl::getScreenHeight() const
{
    return screenHeight;
}

unsigned int frts::GraphicDataImpl::getScreenOffsetStepX() const
{
    return screenOffsetStepX;
}

unsigned int frts::GraphicDataImpl::getScreenOffsetStepY() const
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

unsigned int frts::GraphicDataImpl::getScreenWidth() const
{
    return screenWidth;
}

unsigned int frts::GraphicDataImpl::getTileHeight() const
{
    return tileHeight;
}

unsigned int frts::GraphicDataImpl::getTileWidth() const
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
    return 1;
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

void frts::GraphicDataImpl::setScreenHeight(unsigned int screenHeight)
{
    this->screenHeight = screenHeight;
}

void frts::GraphicDataImpl::setScreenOffsetStepX(unsigned int offsetStep)
{
    this->screenOffsetStepX = offsetStep;
}

void frts::GraphicDataImpl::setScreenOffsetStepY(unsigned int offsetStep)
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

void frts::GraphicDataImpl::setScreenWidth(unsigned int screenWidth)
{
    this->screenWidth = screenWidth;
}

void frts::GraphicDataImpl::setTileHeight(unsigned int tileHeight)
{
    this->tileHeight = tileHeight;
}

void frts::GraphicDataImpl::setTileWidth(unsigned int tileWidth)
{
    this->tileWidth = tileWidth;
}

void frts::GraphicDataImpl::setZLevel(Point::value zLevel)
{
    this->zLevel = zLevel;
}
