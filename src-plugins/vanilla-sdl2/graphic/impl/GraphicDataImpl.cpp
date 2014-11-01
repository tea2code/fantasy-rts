#include "GraphicDataImpl.h"


std::string frts::GraphicDataImpl::getName() const
{
    return "frts::GraphicData";
}

int frts::GraphicDataImpl::getScreenHeight() const
{
    return screenHeight;
}

std::string frts::GraphicDataImpl::getScreenTitle() const
{
    return screenTitle;
}

int frts::GraphicDataImpl::getScreenWidth() const
{
    return screenWidth;
}

int frts::GraphicDataImpl::getTileHeight() const
{
    return tileHeight;
}

int frts::GraphicDataImpl::getTileWidth() const
{
    return tileWidth;
}

void frts::GraphicDataImpl::setScreenHeight(int screenHeight)
{
    this->screenHeight = screenHeight;
}

void frts::GraphicDataImpl::setScreenTitle(const std::string& screenTitle)
{
    this->screenTitle = screenTitle;
}

void frts::GraphicDataImpl::setScreenWidth(int screenWidth)
{
    this->screenWidth = screenWidth;
}

void frts::GraphicDataImpl::setTileHeight(int tileHeight)
{
    this->tileHeight = tileHeight;
}

void frts::GraphicDataImpl::setTileWidth(int tileWidth)
{
    this->tileWidth = tileWidth;
}
