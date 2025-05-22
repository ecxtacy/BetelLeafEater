#pragma once

#include "SDL2/SDL.h"
#include "structs.h"
#include "SDL_image.h"
#include "display.h"
#include <iostream>
#include "defs.h"
#include "map.h"
#include "game_object.h"

class Game {
public:
  Game();
  ~Game();

  /* Initialize SDL Subsystems, window, renderer etc. */
  void init(const char* title, int xpos, int ypos, bool fullscreen);

  void handleEvents();
  void update();
  void render();

  /* Clean the heap objects. */
  void clean();

  /* Check status if game is running */
  bool running();

  /* Display controller object. */
  static ScreenDisplay* display;

  /* Renderer object */
  static SDL_Renderer* renderer;

  /* Map Data Structure holding different entities in the game. */
  static std::unordered_map<std::string, GameEntity*> entities; 
  
  /* Main game player object */
  static Player* player;

private:
  bool isRunning;
  SDL_Window* window;
  GameMap* map;
};