#pragma once

#include <unordered_map>
#include "../entities/tile.h"

/**
 * @class TileKeeper
 * @brief Stores a map data structure keeping record of all Tile objects.
 */
class TileKeeper {
  public:
    static std::unordered_map<int, Tile*> tile_map;
    static int get_next_id();
  private:
    static int available_id;
};