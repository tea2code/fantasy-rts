#include "SpriteManager.h"

#include "SpritePoint.h"
#include <frts/random.h>
#include <frts/vanillamodel>

#include <boost/format.hpp>

#include <numeric>
#include <utility>
#include <vector>


frts::SpriteManager::SpriteManager()
{
}

frts::Sprite frts::SpriteManager::getSprite(RenderablePtr renderable, EntityPtr entity, SharedManagerPtr shared)
{
    assert(renderable != nullptr);
    assert(entity != nullptr);
    assert(shared != nullptr);

    // Get sprite with support of movable for direction.
    auto spriteId = renderable->getSprite();
    SpriteMap::iterator it;
    bool foundSprite = false;

    auto movableId = shared->makeId(ComponentIds::movable());
    if (entity->hasComponent(movableId))
    {
        auto movable = std::static_pointer_cast<Movable>(entity->getComponent(movableId));
        auto direction = movable->getDirection();
        std::string spriteDirection = "south";
        if (direction == Movable::Direction::North)
        {
            spriteDirection = "north";
        }
        else if (direction == Movable::Direction::West)
        {
            spriteDirection = "west";
        }
        else if (direction == Movable::Direction::East)
        {
            spriteDirection = "east";
        }

        auto movableSpriteId = shared->makeId(spriteId->toString() + "." + spriteDirection);
        it = sprites.find(movableSpriteId);
        foundSprite = (it != sprites.end());
    }

    if (!foundSprite)
    {
        it = sprites.find(spriteId);
        if (it == sprites.end())
        {
            // Get fallback.
            it = sprites.find(fallback);
        }
    }
    auto sprite = it->second;

    // Select sprite index.
    if (!renderable->isSpriteIndexSet())
    {
        auto spritePoints = sprite.getSpritePoints();

        // The following little algorithm randomly selects the sprite point using the chances
        // of all sprite points in a sum, throwing a dice and then iterating of the sprite points
        // and checking if the dice value is int he chance interval of the current sprite point.
        // The advantage is that it doesn't matter what values the chances are.
        double upper = std::accumulate(spritePoints.begin(), spritePoints.end(), 0.0,
                                       [](double sum, SpritePoint sp) { return sum + sp.getChance(); });
        double dice = frts::randomFloat(0.0, upper);
        double chanceFrom = 0.0;
        int spriteIndex = 0;
        for (auto& spritePoint : spritePoints)
        {
            if (chanceFrom <= dice && dice <= chanceFrom + spritePoint.getChance())
            {
                break;
            }

            chanceFrom += spritePoint.getChance();
            spriteIndex += 1;
        }
        renderable->setSpriteIndex(spriteIndex);
    }
    sprite.setSpritePointIndex(renderable->getSpriteIndex());

    return sprite;
}

void frts::SpriteManager::setConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr spritesNode)
{
    assert(shared != nullptr);
    assert(spritesNode != nullptr);

    // Namepspace.
    std::string ns = rootNamespace;
    if (spritesNode->has("namespace"))
    {
        ns = ns + "." + spritesNode->getString("namespace");
    }

    // Fallback.
    if (spritesNode->has("fallback"))
    {
        fallback = shared->makeId(spritesNode->getString("fallback"));
    }

    // Height.
    int defaultHeight = -1;
    if (spritesNode->has("height"))
    {
        defaultHeight = spritesNode->getInteger("height");
    }

    // Image.
    IdPtr defaultImage;
    if (spritesNode->has("image"))
    {
        defaultImage = shared->makeId(spritesNode->getString("image"));
    }

    // Width.
    int defaultWidth = -1;
    if (spritesNode->has("width"))
    {
        defaultWidth = spritesNode->getInteger("width");
    }

    // Sprites.
    auto node = spritesNode->getNode("sprite");
    for (auto spriteNode : *node)
    {
        // ID.
        auto id = shared->makeId(ns + "." + spriteNode->getString("name"));

        // Height.
        int height = defaultHeight;
        if (spriteNode->has("height"))
        {
            height = spriteNode->getInteger("height");
        }
        if (height < 0)
        {
            auto msg = boost::format(R"(SpriteManager: Height missing for sprite "%1%".)") % id->toString();
            throw InvalidSpriteConfigError(msg.str());
        }

        // Image.
        auto image = defaultImage;
        if (spriteNode->has("image"))
        {
            image = shared->makeId(spriteNode->getString("image"));
        }
        if (image == nullptr)
        {
            auto msg = boost::format(R"(SpriteManager: Image missing for sprite "%1%".)") % id->toString();
            throw InvalidSpriteConfigError(msg.str());
        }

        // Width.
        int width = defaultWidth;
        if (spriteNode->has("width"))
        {
            width = spriteNode->getInteger("width");
        }
        if (width < 0)
        {
            auto msg = boost::format(R"(SpriteManager: Width missing for sprite "%1%".)") % id->toString();
            throw InvalidSpriteConfigError(msg.str());
        }

        // Sprite points.
        std::vector<SpritePoint> spritePoints;
        if (spriteNode->has("multiple"))
        {
            auto multiplesNode = spriteNode->getNode("multiple");
            for (auto multipleNode : *multiplesNode)
            {
                int x = multipleNode->getInteger("x");
                int y = multipleNode->getInteger("y");
                double chance = 1.0;
                if (multipleNode->has("chance"))
                {
                    chance = multipleNode->getFloat("chance");
                }
                SpritePoint spritePoint(x, y, chance);
                spritePoints.push_back(spritePoint);
            }
        }
        else
        {
            int x = spriteNode->getInteger("x");
            int y = spriteNode->getInteger("y");
            SpritePoint spritePoint(x, y);
            spritePoints.push_back(spritePoint);
        }

        Sprite sprite (image, height, width, spritePoints);
        sprites.insert(std::make_pair(id, sprite));
    }

    isConfigInitialized = true;
}

void frts::SpriteManager::validateData(SharedManagerPtr)
{
    // Is fallback set.
    if (fallback == nullptr)
    {
        auto msg = boost::format(R"(SpriteManager: Fallback sprite ID missing.)");
        throw InvalidSpriteConfigError(msg.str());
    }
    // If so check if fallback sprite exists.
    else if (sprites.find(fallback) == sprites.end())
    {
        auto msg = boost::format(R"(SpriteManager: Fallback sprite for ID "%1%" missing.)") % fallback->toString();
        throw InvalidSpriteConfigError(msg.str());
    }
}
