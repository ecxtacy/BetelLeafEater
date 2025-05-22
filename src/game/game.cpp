#include "game.h"
#include "game_object.h"
#include <utility>
#include "../entities/lassi.h"
#include "../entities/watermelon.h"
#include "tile_keeper.h"
#include "texture_manager.h"

// STATIC OBJECTS ------------------------------------------------

ScreenDisplay* Game::display = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Player* Game::player = nullptr;

// --------------------------------------------------------

// Declare the DS that will hold different GameEntities.
std::unordered_map<std::string, GameEntity*> Game::entities;

Game::Game() 
{};

Game::~Game() 
{};

void Game::init(const char* title, int xpos, int ypos, bool fullscreen) 
{
  int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

  // Initialize SDL Subsystems.
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Unable to initialize SDL Subsystem" << std::endl;
    Game::isRunning = false;
    return;
  }

  std::cout << "SDL systems initialized" << std::endl;

  // Create Display, Window and Renderer objects.
  Game::display = new ScreenDisplay(title, xpos, ypos, SCREEN_HEIGHT, SCREEN_WIDTH, FPS);
  Game::window = Game::display->init_window(fullscreen);
  Game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if(!Game::renderer) {
    std::cerr << "Error creating the window" << std::endl;
    Game::isRunning = false;
    return;
  }

  // Check if images can be loaded successfully.
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "Failed to init SDL_image: " << IMG_GetError() << std::endl;
    isRunning = false;
    return;
  }

  // Todo: Add a better module / function for game level data generation and loading.
  // Todo: Should read data from a file, and then initialize the objects through it.
  {
    Game::player = new Player("assets/sahil.png", "assets/sahil_raged.png");
    Game::player->set_texture_portion({0, 0, 16, 32});
  
    // ! DEBUGGING
    Game::player->set_gravitational_object(true);
    Game::player->set_dimensions(70, 140);
    Game::player->set_velocity(0, 0);
  
    Lassi* lassi = new Lassi("assets/lassi.png");
    lassi->set_dimensions(75, 75);
    lassi->set_position(500, (int)FLOOR_BORDER_Y - 100);
    Game::entities["lassi"] = static_cast<GameEntity*>(lassi);
  
    Watermelon* watermelon = new Watermelon("assets/watermelon.png");
    watermelon->set_dimensions(60, 60);
    watermelon->set_position(800, (int)FLOOR_BORDER_Y - 100);
    Game::entities["watermelon"] = static_cast<GameEntity*>(watermelon);
  
    map = new GameMap();
    map->load_textures();
    map->load_map("maps/level_0.map");
  }

  // Mark game is running, since all systems have been initialized and loaded successfully.
  isRunning = true;
};

/* This function will catch any event and call the event handler of all objects in the game. */
void Game::handleEvents() {

  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
    case SDL_QUIT:
      Game::isRunning = false;
      break;
    
    default:
      std::unordered_map<std::string, GameEntity*>::iterator it;
      for(it = entities.begin(); it != entities.end(); it++) {
        GameEntity* entity = it->second;
        entity->handle_events(&event);
      }
      break;
  }

  Game::player->handle_events(&event);
};

/* Update the values / attributes of game objects. This gets called in every frame. */
void Game::update() {
  Game::player->update();

  for(auto it = entities.begin(); it != entities.end(); it++) {
    std::pair<std::string, GameEntity*> e = *it;
    auto [entity_name, entity] = e;
    entity->update();
  }

};

void Game::render() {

  // Refresh the buffer.
  SDL_RenderClear(renderer);

  // Render map first.
  map->render();
  
  Game::player->render();

  for(auto it = entities.begin(); it != entities.end(); it++) {
    std::pair<std::string, GameEntity*> e = *it;
    auto [entity_name, entity] = e;
    entity->render();
  }

  // Present the buffer to GPU and display out to screen.
  SDL_RenderPresent(renderer);
};

// Clean, clear and deallocate objects and data structures.
void Game::clean () {
  SDL_DestroyWindow(window);
  window = nullptr;

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  for(auto& [e_name, entity] : entities) {
    entity->clean();
  }

  player->clean();

  // Deallocate and clear the entities map data structure.
  entities.clear();

  SDL_Quit();

  std::cout << "Game cleaned" << std::endl;
};

bool Game::running() {
  return Game::isRunning;
}

