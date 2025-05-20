#include "tile_keeper.h"

// STATICS

std::unordered_map<int, Tile*> TileKeeper::tile_map;
int TileKeeper::available_id = 0;

int TileKeeper::get_next_id() 
{
  return available_id++;
}