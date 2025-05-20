#include "map.h"
#include "defs.h"
#include "texture_manager.h"
#include <fstream>
#include "../entities/tile.h"
#include "tile_keeper.h"

GameMap::GameMap() 
{}; 

GameMap::~GameMap() 
{
  SDL_DestroyTexture(brick);
}

void GameMap::load_textures() 
{
  brick = TextureManager::load_texture("assets/brick.png");
}

void GameMap::render() {

  // Render the tiles from the map data which has been loaded.
  for(auto it = TileKeeper::tile_map.begin(); it != TileKeeper::tile_map.end(); ++it) {
    auto [_id, tile] = *it;
    tile->render();
  }

}

void GameMap::setRenderBGColor(ColorRGBA color) 
{
  SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
}

void GameMap::load_map(const char* filepath) {

  // Read through a filestream and store the data in a Data Structure.
  std::cout << "Opening: " << filepath << std::endl;
  std::fstream file;
  file.open(filepath, std::ios::in);

  if(!file) {
    std::cerr << "No file" << std::endl;
    exit(1);
  } else {
    std::cout << "File opened successfully" << std::endl;
  }

  // Todo: Improvise parsing of map data through files.

  char ch;
  int start_x = 0;

  for(int x = 0; x < GAME_TILE_COL_COUNT; x++) {

    int start_y = SCREEN_HEIGHT - TILE_H;
    for(int y = 0; y < GAME_TILE_ROW_COUNT; y++) {
      file.get(ch);
      int tile_type = ch - '0';

      if(tile_type != NONE) {
        Tile* t = new Tile(tile_type, TileKeeper::get_next_id());
        
        // todo: set a standard tile dimension
        t->set_texture_dimension(18, 16);
        t->set_dst_rect(start_x, start_y, TILE_W, TILE_H);
        
        // Insert into the tilemap
        TileKeeper::tile_map[t->get_id()] = t;

      }
      start_y -= TILE_H;

      // Ignore the next character, (comma according to current formatting of map file)
      file.ignore();
    }
    
    start_x += TILE_W;

    // If EOF reached, exit
    if(!file.get(ch)) break;
  }

  file.close();
}