#include "tile.h"
#include "../game/texture_manager.h"

// STATIC
const char* Tile::tile_texture_path[3] = {
  nullptr,
  "assets/brick.png",
};

void Tile::set_dst_rect(int x, int y, int w, int h) {
  dst_rect = {x, y, w, h};
}

void Tile::update() 
{};

void Tile::render() 
{
  TextureManager::Draw(tile_texture, src_rect, dst_rect);
};

Tile::Tile(int t, int _id) 
{
  type = t;
  tile_texture = TextureManager::load_texture(tile_texture_path[t]);
  id = _id;
};

Tile::~Tile() 
{
  SDL_DestroyTexture(tile_texture);
};

int Tile::get_id() {
  return id;  
}

void Tile::set_texture_dimension(int w, int h) {
  src_rect.w = w;
  src_rect.h = h;
  src_rect.x = src_rect.y = 0;
}

SDL_Rect Tile::get_dst_rect() {
  return dst_rect;
}

std::vector<struct Point> Tile::get_bounding_rect() {
  std::vector<struct Point> b_rect = {
    {dst_rect.x, dst_rect.y},
    {dst_rect.x + dst_rect.w, dst_rect.y},
    {dst_rect.x, dst_rect.y + dst_rect.h},
    {dst_rect.x + dst_rect.w, dst_rect.y + dst_rect.h}
  };
  return b_rect;
}