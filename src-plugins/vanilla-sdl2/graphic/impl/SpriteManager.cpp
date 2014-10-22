#include "SpriteManager.h"

#include "SpritePoint.h"

#include <boost/format.hpp>

#include <utility>
#include <vector>


frts::SpriteManager::SpriteManager()
{
}

frts::Sprite frts::SpriteManager::getSprite(RenderablePtr renderable)
{
    return frts::Sprite(nullptr, 0, 0, {});
}

void frts::SpriteManager::setConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr spritesNode)
{
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
    for (auto spriteNode : *spritesNode->getNode("sprite"))
    {
        // ID.
        IdPtr id = shared->makeId(ns + "." + spriteNode->getString("name"));

        // Height.
        int height = defaultHeight;
        if (spriteNode->has("height"))
        {
            height = spriteNode->getInteger("height");
        }
        if (height < 0)
        {
            auto msg = boost::format(R"(Height missing for sprite "%1%".)") % id->toString();
            throw InvalidSpriteConfigError(msg.str());
        }

        // Image.
        IdPtr image = defaultImage;
        if (spriteNode->has("image"))
        {
            image = shared->makeId(spriteNode->getString("image"));
        }
        if (image == nullptr)
        {
            auto msg = boost::format(R"(Image missing for sprite "%1%".)") % id->toString();
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
            auto msg = boost::format(R"(Width missing for sprite "%1%".)") % id->toString();
            throw InvalidSpriteConfigError(msg.str());
        }

        // Sprite points.
        std::vector<SpritePoint> spritePoints;
        if (spriteNode->has("multiple"))
        {
            for (auto multipleNode : *spriteNode->getNode("multiple"))
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
}
