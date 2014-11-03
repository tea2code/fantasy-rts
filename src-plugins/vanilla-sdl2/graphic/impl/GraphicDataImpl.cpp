#include "GraphicDataImpl.h"


unsigned int frts::GraphicDataImpl::getMaxFps() const
{
    return maxFps;
}

std::string frts::GraphicDataImpl::getName() const
{
    return "frts::GraphicData";
}

unsigned int frts::GraphicDataImpl::getScreenHeight() const
{
    return screenHeight;
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

frts::Point::value frts::GraphicDataImpl::getZLevel() const
{
    return zLevel;
}

bool frts::GraphicDataImpl::isRenderEverything() const
{
    return renderEverything;
}

void frts::GraphicDataImpl::setMaxFps(unsigned int maxFps)
{
    this->maxFps = maxFps;
}

void frts::GraphicDataImpl::setRenderEverything(bool renderEverything)
{
    this->renderEverything = renderEverything;
}

void frts::GraphicDataImpl::setScreenHeight(unsigned int screenHeight)
{
    this->screenHeight = screenHeight;
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
