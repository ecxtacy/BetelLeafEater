#pragma once
#include "SDL2/SDL.h"
#include "defs.h"
#include "structs.h"
#include <unordered_map>

class GameMap {
  public:
    GameMap();
    ~GameMap();

    /* Load the tiles and map image textures in the RAM beforehand. */
    void load_textures();

    void update();
    void render();
    void clean();

    /* Load the map from a map data file, and store the data in appropriate data structures. */
    void load_map(const char* filepath);

  private:

    // Keep the different textures (water, sand, brick, etc here)
    SDL_Texture* brick;

    /* Set the background color of the screen. */
    void setRenderBGColor(ColorRGBA colors);

    // ? Maybe shift the initialization to map.cpp ?
    std::unordered_map<Colors, ColorRGBA> ColorValue = {
      {COLOR_WHITE, {255, 255, 255, 0}},
      {COLOR_BLACK, {0, 0, 0, 0}},
      {COLOR_RED, {255, 0, 0, 0}},
      {COLOR_GREEN, {0, 255, 0, 0}},
      {COLOR_BLUE, {30, 200, 250, 0}},
      {COLOR_YELLOW, {255, 0, 255, 0}}
    };
};