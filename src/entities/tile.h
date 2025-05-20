#pragma once
#include "../abstract/entity.h"

enum TileType {
  NONE,
  BRICK
};

/**
 * @class Tile
 */
class Tile {
  public:
    Tile(int t, int _id);
    ~Tile();

    void update();
    void render();

    void set_texture_dimension(int w, int h);
    void set_dst_rect(int x, int y, int w, int h);

    std::vector<struct Point> get_bounding_rect();

    SDL_Rect get_dst_rect();

    int get_id();

  private:
    int type;
    SDL_Rect src_rect, dst_rect;
    SDL_Texture* tile_texture;

    int id;

    static const char* tile_texture_path[3];
};