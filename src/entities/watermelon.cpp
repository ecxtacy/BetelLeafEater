#include "watermelon.h"
#include "../game/game.h"
#include "../game/texture_manager.h"

Watermelon::Watermelon(const char* texture_path) {
  Watermelon::melon_texture = TextureManager::load_texture(texture_path);
  Watermelon::src_rect = {
    x: 0,
    y: 0,
    w: 15,
    h: 15,
  };
  used = false;
};

Watermelon::~Watermelon() {
  SDL_DestroyTexture(melon_texture);
};

void Watermelon::update() {
};

void Watermelon::render() {

  int sprite_frame = (int)(4 * Game::display->get_elapsed_frames() / (Game::display->get_avg_fps())) % 4;
  src_rect.x = sprite_frame * 15;

  if(!used) {
    TextureManager::Draw(melon_texture, src_rect, dst_rect);
  }
};
void Watermelon::handle_events(SDL_Event* event) {};
void Watermelon::clean() {};

std::vector<struct Point> Watermelon::get_bounding_rect() {

  std::vector<struct Point> b_rect = {
    {dst_rect.x, dst_rect.y},
    {dst_rect.x + dst_rect.w, dst_rect.y},
    {dst_rect.x, dst_rect.y + dst_rect.h},
    {dst_rect.x + dst_rect.w, dst_rect.y + dst_rect.h}
  };

  return b_rect;
};


bool Watermelon::touching(Player* player) {
  std::vector<struct Point> prect = player->get_bounding_rect();
  std::vector<struct Point> lrect = Watermelon::get_bounding_rect();

  if(prect[3].x <= lrect[0].x || lrect[3].x <= prect[0].x) {
    return false;
  }

  if(prect[3].y <= lrect[0].y || lrect[3].y <= prect[0].y) {
    return false;
  }

  return true;
}

void Watermelon::set_position(float xpos, float ypos) {
  dst_rect.x = xpos;
  dst_rect.y = ypos;
}

void Watermelon::set_dimensions(int w, int h) {
  dst_rect.w = w;
  dst_rect.h = h;
}

void Watermelon::interact() {
  if(touching(Game::player)) {
    // std::cout << "watermelon touching player" << std::endl;
    Game::player->get_raged();
    used = true;
  } else {
    // std::cout << "watermelon not touching player" << std::endl;
  }
}

bool Watermelon::is_used() {
  return used;
}