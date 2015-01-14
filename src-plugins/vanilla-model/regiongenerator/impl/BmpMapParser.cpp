#include "BmpMapParser.h"

#include <entity/ComponentIds.h>
#include <main/ModelData.h>
#include <main/ModelFactory.h>
#include <main/ModelIds.h>
#include <main/RegionManager.h>
#include <region/impl/BlockImpl.h>
#include <frts/shared>

#include <boost/format.hpp>

#include <algorithm>
#include <cmath>


frts::BmpMapParser::BmpMapParser(IdPtr blockingType, IdPtr sortOrderType, IdPtr teleportType)
    : blockingType{blockingType}, sortOrderType{sortOrderType}, teleportType{teleportType}
{
}

frts::EntityPtr frts::BmpMapParser::connectIfNotYet(WriteableBlockPtr block, PointPtr otherPos,
                                                    const EntityVector& targets, SharedManagerPtr shared)
{
    assert(block != nullptr);
    assert(otherPos != nullptr);
    assert(shared != nullptr);

    auto otherBlock = getBlock(otherPos, shared);

    // Are we already connected?
    for (auto& entity : otherBlock->getByComponent(teleportType))
    {
        if (std::find(targets.begin(), targets.end(), entity) != targets.end())
        {
            return nullptr;
        }
    }

    // Not yet connected so let's do that.
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto target = mf->makeEntity();
    auto otherTarget = mf->makeEntity();

    auto teleport = std::static_pointer_cast<Teleport>(mf->makeComponent(teleportType, shared));
    teleport->setTarget(otherTarget);
    target->addComponent(teleport);

    auto otherTeleport = std::static_pointer_cast<Teleport>(mf->makeComponent(teleportType, shared));
    otherTeleport->setTarget(target);
    otherTarget->addComponent(otherTeleport);

    block->insert(target);
    otherBlock->insert(otherTarget);

    return otherTarget;
}

frts::WriteableBlockPtr frts::BmpMapParser::getBlock(PointPtr pos, SharedManagerPtr shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    frts::WriteableBlockPtr block;

    auto bIt = blocks.find(pos);
    if (bIt != blocks.end())
    {
        block = bIt->second;
    }
    else
    {
        auto mpIt = mapPoints.find(pos);
        if (mpIt != mapPoints.end())
        {
            auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
            block = mf->makeBlock(shared);

            auto& rgb = mpIt->second;
            auto cIt = colors.find(rgb);
            if (cIt != colors.end())
            {
                for (auto& entityId : cIt->second)
                {
                    block->insert(mf->makeEntity(entityId, shared));
                }
            }
            else
            {
                auto msg = boost::format(R"(Unknown color (%1%, %2%, %3%) at position (%4%, %5%, %6%).)")
                        % std::get<0>(rgb) % std::get<1>(rgb) % std::get<2>(rgb)
                        % pos->getX() % pos->getY() % pos->getZ();
                shared->getLog()->warning("frts::BmpMapParser", msg.str());
            }

            blocks[pos] = block;
        }
    }

    return block;
}

std::string frts::BmpMapParser::getSupportedConfig() const
{
    return "bmp_map";
}

void frts::BmpMapParser::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto md = getDataValue<MainData>(shared, MainIds::mainData());
    for (auto& level : levels)
    {
        parseMap(md->getPluginPath() + images.at(level.second), level.first, shared);
    }
}

frts::WriteableBlockPtr frts::BmpMapParser::newBlock(PointPtr pos, SharedManagerPtr shared)
{
    assert(pos != nullptr);
    assert(shared != nullptr);

    frts::WriteableBlockPtr block = getBlock(pos, shared);

    if (block != nullptr)
    {
        // Teleport slopes.
        tryConnectTeleport(pos, block, teleportUp, teleportDown, +1, shared);
        tryConnectTeleport(pos, block, teleportDown, teleportUp, -1, shared);

        // Teleport portals.
        auto mpIt = mapPoints.find(pos);
        if (mpIt != mapPoints.end())
        {
            auto tIt = teleporters.find(mpIt->second);
            if (tIt != teleporters.end())
            {
                // Do we already have teleport components in this block?
                EntityVector targets;
                for (auto& entity : block->getByComponent(teleportType))
                {
                    auto teleport = getComponent<Teleport>(teleportType, entity);
                    targets.push_back(teleport->getTarget());
                }

                auto tpIt = teleporterPoints.find(tIt->second);
                if (tpIt != teleporterPoints.end())
                {
                    for (auto& teleportPos : tpIt->second)
                    {
                        if (teleportPos == pos)
                        {
                            continue;
                        }

                        // Connect if not already happened.
                        connectIfNotYet(block, teleportPos, targets, shared);

                        // Portals only exist between two points so break after the first other block.
                        break;
                    }
                }
            }
        }
    }

    return block;
}

void frts::BmpMapParser::parseConfig(ConfigNodePtr node, SharedManagerPtr shared)
{
    assert(node != nullptr);
    assert(shared != nullptr);

    std::string ns = node->getString("namespace", "");
    if (!ns.empty())
    {
        ns += ".";
    }

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
            imageNs += imagesNode->getString("namespace") + ".";
        }

        auto imagesListNode = imagesNode->getNode("images");
        for (auto imageNode : *imagesListNode)
        {
            auto id = shared->makeId(imageNs + imageNode->getString("name"));
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

                if (colorNode->has("teleport"))
                {
                    teleporters[rgb] = shared->makeId(colorNode->getString("teleport"));
                }

                IdVector entities;
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
    assert(shared != nullptr);

    // Following BMP parsing is based on http://stackoverflow.com/a/17040962/1931663
    // Supports 24bit color BMP with padding.

    FILE* file = fopen(path.c_str(), "rb");

    if(file == NULL)
    {
        auto msg = boost::format(R"(BmpMapParser: Map file with path "%1%" not found.)") % path;
        throw MapFileNotFoundError(msg.str());
    }

    // Read the 54-byte header.
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file);

    // Extract image height and width from header.
    auto md = getDataValue<ModelData>(shared, ModelIds::modelData());
    int width = std::min(static_cast<int>(info[18]), md->getMapSizeX());
    int height = std::min(static_cast<int>(info[22]), md->getMapSizeY());

    // Precalculate padding.
    int rgbWidth = width * 3;
    int rowPadded = (rgbWidth + 3) & (~3);

    // Read and parse map file.
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    unsigned char* data = new unsigned char[rowPadded];
    for(int y = 0; y < height; ++y)
    {
        fread(data, sizeof(unsigned char), rowPadded, file);

        for(int x = 0; x < width; ++x)
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
            auto pos = mf->makePoint(x, height - 1 - y, zLevel);

            // Is this a teleporter?
            auto it = teleporters.find(rgb);
            if (it != teleporters.end())
            {
                teleporterPoints[it->second].push_back(pos);
            }

            // Store map point.
            mapPoints[pos] = rgb;
        }
    }
    delete[] data;

    fclose(file);
}

void frts::BmpMapParser::tryConnectTeleport(PointPtr pos, WriteableBlockPtr block, const TeleportColors& teleportColorsBlock,
                                            const TeleportColors& teleportColorsOther, Point::value zLevelChange, SharedManagerPtr shared)
{
    assert(pos != nullptr);
    assert(block != nullptr);
    assert(shared != nullptr);

    // Not really proud of this. But it was the most clear solution i found. I'm open to better implementations or complete
    // replacements of the teleport component.

    auto mpIt = mapPoints.find(pos);
    if (mpIt != mapPoints.end() && teleportColorsBlock.find(mpIt->second) != teleportColorsBlock.end())
    {
        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

        // Do we already have teleport components in this block?
        EntityVector targets;
        for (auto& entity : block->getByComponent(teleportType))
        {
            auto teleport = getComponent<Teleport>(teleportType, entity);
            targets.push_back(teleport->getTarget());
        }

        // This is a teleport up block. Check for matching teleport blocks.
        auto posDown = mf->makePoint(pos->getX(), pos->getY(), pos->getZ() + zLevelChange);
        auto neighbors = rm->getNeightbors(posDown, true, shared);
        for (auto& neighborPos : neighbors)
        {
            // Is this a teleport block?
            auto nMpIt = mapPoints.find(neighborPos);
            if (nMpIt == mapPoints.end() || teleportColorsOther.find(nMpIt->second) == teleportColorsOther.end())
            {
                // Nope it isn't :(
                continue;
            }

            // Connect if not already happened.
            auto otherTarget = connectIfNotYet(block, neighborPos, targets, shared);

            // Did we connect to another target?
            if (otherTarget == nullptr)
            {
                break;
            }

            // Register other target in region manager. This may seem like a recursive call but
            // at this point
            // 1. the relevant information for the current block and the new target is already setup
            // 2. because there is no diagonal movement possible it's quite hard to construct a
            //    chain of target block initialization
            rm->setPos(otherTarget, neighborPos, shared);
        }
    }
}

void frts::BmpMapParser::validateData(SharedManagerPtr)
{
    if (height == 0)
    {
        throw DataViolation("BmpMapParser: Height in bitmap map configuration must be greater than zero.");
    }

    if (width == 0)
    {
        throw DataViolation("BmpMapParser: Width in bitmap map configuration must be greater than zero.");
    }
}
