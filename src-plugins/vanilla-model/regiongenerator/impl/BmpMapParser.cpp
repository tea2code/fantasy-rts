#include "BmpMapParser.h"

#include <entity/ComponentIds.h>
#include <main/ModelData.h>
#include <main/ModelFactory.h>
#include <main/ModelIds.h>
#include <main/RegionManager.h>
#include <region/impl/BlockImpl.h>
#include <frts/shared>

#include <boost/format.hpp>

#include <cmath>


frts::BmpMapParser::BmpMapParser(IdPtr blockingType, IdPtr sortOrderType)
    : blockingType{blockingType}, sortOrderType{sortOrderType}
{
}

std::string frts::BmpMapParser::getSupportedConfig()
{
    return "bmpmap";
}

void frts::BmpMapParser::init(SharedManagerPtr shared)
{
    auto md = getDataValue<MainData>(shared, MainIds::mainData());
    for (auto& level : levels)
    {
        parseMap(md->getPluginPath() + images.at(level.second), level.first, shared);
    }
}

frts::WriteableBlockPtr frts::BmpMapParser::newBlock(PointPtr pos, SharedManagerPtr shared)
{
    frts::WriteableBlockPtr block;

    auto mpIt = mapPoints.find(pos);
    if (mpIt != mapPoints.end())
    {
        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

        block = makeBlock(blockingType, sortOrderType);

        // Teleport.
        auto tIt = teleportUp.find(mpIt->second);
        if (tIt != teleportUp.end())
        {
            auto posUp = mf->makePoint(pos->getX(), pos->getY(), pos->getZ() + 1);
            auto neighbors = rm->getNeightbors(posUp, true, shared);
            for (auto& neighbor : neighbors)
            {
                auto mptIt = mapPoints.find(neighbor);
                if (mptIt != mapPoints.end())
                {
                    tIt = teleportDown.find(mptIt->second);
                    if (tIt != teleportDown.end())
                    {
                        auto tpIt = teleportDownPositions.find(neighbor);
                        if (tpIt != teleportDownPositions.end() && tpIt->second.find(pos) != tpIt->second.end())
                        {

                        }
                    }
                }
            }
        }
        // TODO Down

        auto cIt = colors.find(mpIt->second);
        if (cIt != colors.end())
        {
            for (auto& entityId : cIt->second)
            {
                block->insert(mf->makeEntity(entityId, shared));
            }
        }
    }

    return block;
}

void frts::BmpMapParser::parseConfig(ConfigNodePtr node, SharedManagerPtr shared)
{
    std::string ns = node->getString("namespace", "");
    height = node->getInteger("height", height);
    width = node->getInteger("width", width);

    // Levels.
    if (node->has("levels"))
    {
        auto levelsNode = node->getNode("levels");
        for (auto levelNode : *levelsNode)
        {
            levels[levelNode->getInteger("level")] = shared->makeId(levelNode->getString("image"));
        }
    }

    // Images.
    if (node->has("images"))
    {
        auto imagesNode = node->getNode("images");

        std::string imageNs = ns;
        if (imagesNode->has("namespace"))
        {
            imageNs += "." + imagesNode->getString("namespace");
        }

        auto imagesListNode = imagesNode->getNode("images");
        for (auto imageNode : *imagesListNode)
        {
            auto id = shared->makeId(imageNs + "." + imageNode->getString("name"));
            images[id] = imageNode->getString("path");
        }
    }

    // Colors.
    if (node->has("colors"))
    {
        auto colorsNode = node->getNode("colors");

        if (colorsNode->has("neutral"))
        {
            auto neutralNode = colorsNode->getNode("neutral");

            int r = neutralNode->getInteger("r");
            int g = neutralNode->getInteger("g");
            int b = neutralNode->getInteger("b");

            neutralColor = std::make_tuple(r, g, b);
        }

        if (colorsNode->has("colors"))
        {
            auto colorsListNode = colorsNode->getNode("colors");
            for (auto colorNode : *colorsListNode)
            {
                int r = colorNode->getInteger("r");
                int g = colorNode->getInteger("g");
                int b = colorNode->getInteger("b");
                auto rgb = std::make_tuple(r, g, b);

                if (colorNode->has("teleport_up") && colorNode->getBool("teleport_up"))
                {
                    teleportUp.insert(rgb);
                }

                if (colorNode->has("teleport_down") && colorNode->getBool("teleport_down"))
                {
                    teleportDown.insert(rgb);
                }

                std::vector<IdPtr> entities;
                for (auto& entity : colorNode->getStrings("entities"))
                {
                    entities.push_back(shared->makeId(entity));
                }
                colors[rgb] = entities;
            }
        }
    }
}

void frts::BmpMapParser::parseMap(const std::string& path, Point::value zLevel, SharedManagerPtr shared)
{
    // Following BMP parsing is based on http://stackoverflow.com/a/17040962/1931663
    // Supports 24bit color BMP with padding.

    FILE* file = fopen(path.c_str(), "rb");

    if(file == NULL)
    {
        auto msg = boost::format(R"(Map file with path "%1% not found.)") % path;
        throw MapFileNotFoundError(msg.str());
    }

    // Read the 54-byte header.
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file);

    // Extract image height and width from header.
    auto md = getDataValue<ModelData>(shared, ModelIds::modelData());
    int width = std::min(*(int*)&info[18], md->getMapSizeX());
    int height = std::min(*(int*)&info[22], md->getMapSizeY());
    int rgbWidth = width * 3;

    // Precalculate padding.
    int rowPadded = (rgbWidth + 3) & (~3);

    // Read and parse map file.
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    unsigned char* data = new unsigned char[rowPadded];
    for(int y = 0; y < height; ++y)
    {
        fread(data, sizeof(unsigned char), rowPadded, file);
        for(int x = 0; x < rgbWidth; ++x)
        {
            int nextRgb = 3 * x;
            int r = static_cast<int>(data[nextRgb + 2]);
            int g = static_cast<int>(data[nextRgb + 1]);
            int b = static_cast<int>(data[nextRgb]);
            auto rgb = std::make_tuple(r, g, b);

            if (rgb == neutralColor)
            {
                continue;
            }

            // Because the y axis in bitmap images is reversed we must invert the value.
            mapPoints[mf->makePoint(x, height - 1 - y, zLevel)] = rgb;
        }
    }
    delete[] data;

    fclose(file);
}

void frts::BmpMapParser::validateData(SharedManagerPtr)
{
    if (height == 0)
    {
        throw DataViolation("Height in bitmap map configuration must be greater than zero.");
    }

    if (width == 0)
    {
        throw DataViolation("Width in bitmap map configuration must be greater than zero.");
    }
}
