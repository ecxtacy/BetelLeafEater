#pragma once
#include "../game/game_object.h"

class Lassi: public GameEntity {
  public:

  Lassi(const char* texture_path);
  ~Lassi();

  void update() override;
  void handle_events(SDL_Event* event) override;
  void render() override;
  void clean() override;

  void interact() override;

  void set_position(float xpos, float ypos);
  void set_dimensions(int w, int h);

  std::vector<struct Point> get_bounding_rect();

  bool touching(Player* player);

  bool is_used() override;

  private:
    float pos_x, pos_y;
    SDL_Rect src_rect, dst_rect;
    SDL_Texture* lassi_texture;
    bool used;
};