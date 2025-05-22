#include "lassi.h"
#include "../game/game.h"
#include "../game/texture_manager.h"

Lassi::Lassi(const char* texture_path) {
  Lassi::lassi_texture = TextureManager::load_texture(texture_path);
  Lassi::src_rect = {
    x: 0,
    y: 0,
    w: 16,
    h: 16,
  };
  used = false;
};

Lassi::~Lassi() {
  SDL_DestroyTexture(lassi_texture);
};

void Lassi::update() {
};

void Lassi::render() {
  if(!used) {
    TextureManager::Draw(lassi_texture, src_rect, dst_rect);
  }
};
void Lassi::handle_events(SDL_Event* event) {};
void Lassi::clean() {};

std::vector<struct Point> Lassi::get_bounding_rect() {

  std::vector<struct Point> b_rect = {
    {dst_rect.x, dst_rect.y},
    {dst_rect.x + dst_rect.w, dst_rect.y},
    {dst_rect.x, dst_rect.y + dst_rect.h},
    {dst_rect.x + dst_rect.w, dst_rect.y + dst_rect.h}
  };

  return b_rect;
};

int temp = 0;

bool Lassi::touching(Player* player) {
  std::vector<struct Point> prect = player->get_bounding_rect();
  std::vector<struct Point> lrect = Lassi::get_bounding_rect();

  if(prect[3].x <= lrect[0].x || lrect[3].x <= prect[0].x) {
    return false;
  }

  if(prect[3].y <= lrect[0].y || lrect[3].y <= prect[0].y) {
    return false;
  }

  temp++;
  return true;
}

void Lassi::set_position(float xpos, float ypos) {
  dst_rect.x = xpos;
  dst_rect.y = ypos;
}

void Lassi::set_dimensions(int w, int h) {
  dst_rect.w = w;
  dst_rect.h = h;
}

void Lassi::interact() {
  if(touching(Game::player)) {
    std::cout << "lassi touching player" << std::endl;
    Game::player->powerup();
    used = true;
  } else {
    std::cout << "lassi not touching player" << " temp = " << temp << std::endl;
  }
}

bool Lassi::is_used() {
  return used;
}