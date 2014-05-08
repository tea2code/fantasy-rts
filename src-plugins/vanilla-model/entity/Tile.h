#ifndef FRTS_TILE_H
#define FRTS_TILE_H

#include "Entity.h"

#include <memory>


namespace frts
{
    class Tile;

    /**
     * @brief Pointer to Tile.
     */
    using TilePtr = std::shared_ptr<Tile>;

    /**
     * @brief Tiles represent the current floor. They usually don't allow
     *        any interaction.
     */
    class Tile : public Entity
    {
    public:
        virtual ~Tile() {}
    };
}

#endif // FRTS_TILE_H
