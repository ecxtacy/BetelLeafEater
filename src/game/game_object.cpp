#include "game_object.h"
#include "texture_manager.h"
#include "tile_keeper.h"
#include "../components/collision.h"
#include "../components/vector2D.h"

Player::Player(const char* texture_path, const char* raged_texture_path) {
  object_texture = TextureManager::load_texture(texture_path);
  raged_player_texture = TextureManager::load_texture(raged_texture_path);
  memset(&src_rect, 0, sizeof(SDL_Rect));
  memset(&dst_rect, 0, sizeof(SDL_Rect));

  in_air = true;
  power_level = 0;
  rage_left = 0;
  jumping = false;
}

Player::~Player() {
  SDL_DestroyTexture(object_texture);
  SDL_DestroyTexture(raged_player_texture);
}

void Player::set_texture_portion(SDL_Rect srect) {
  src_rect = srect;
  dst_rect = {10, 10, 2*TILE_W, 2*TILE_H};
}

void Player::set_dimensions(int w, int h) {
  dst_rect.w = w;
  dst_rect.h = h;
}

void Player::set_position(float x, float y) {
  pos_x = x;
  pos_y = y;
}

void Player::set_velocity(float vx, float vy) {
  vel_x = vx;
  vel_y = vy;
}

void Player::set_gravitational_object(bool is_grav_object) {
  apply_gravity = is_grav_object;
  if(apply_gravity) {
    physics.apply_gravity();
  } else {
    physics.remove_gravity();
  }
}

std::vector<struct Point> Player::get_bounding_rect() {
  std::vector<struct Point> b_rect = {
    {dst_rect.x, dst_rect.y},
    {dst_rect.x + dst_rect.w, dst_rect.y},
    {dst_rect.x, dst_rect.y + dst_rect.h},
    {dst_rect.x + dst_rect.w, dst_rect.y + dst_rect.h}
  };
  return b_rect;
}

void Player::handle_events(SDL_Event* event) {
  switch (event->type)
  {
  case SDL_KEYDOWN: {
    const SDL_Scancode keycode = event->key.keysym.scancode;
      if(keycode == SDL_SCANCODE_RIGHT) {
        if(!in_air) { 
          physics.accelerate_x(DELTA_X * Game::display->delta_T());
        } else {
          physics.accelerate_x(DELTA_X / 4 * Game::display->delta_T());
        }
      }

      if (keycode == SDL_SCANCODE_LEFT) {
        if(!in_air) {
          physics.accelerate_x(-DELTA_X * Game::display->delta_T());
        } else {
          physics.accelerate_x(-DELTA_X / 4 * Game::display->delta_T());
        }
      }

      if (keycode == SDL_SCANCODE_UP && !jumping ) {
        physics.accelerate_y(-DELTA_Y * Game::display->delta_T());
        physics.pos += Vector2D(0, -3);
        in_air = true;
        physics.apply_gravity();
        jumping = true;
        std::cout << "UP KEY PRESSED\n";
      }

      // ! FOR DEBUGGING COLLISION WITH WALL
      if(keycode == SDL_SCANCODE_DOWN) {
        physics.vel += Vector2D(0, DELTA_Y * Game::display->delta_T() / 5);
      }
  }
    break;

  default:
    break;
  }

  physics.sync_pos(&dst_rect);
}

void Player::update() {

  physics.apply_gravity();

  if(!in_air) {
    physics.update_friction(GROUND_FRICTION_COEFF);
  } else {
    physics.update_friction(AIR_FRICTION_COEFF);
  }

  bool set_in_air = true;

  for(auto it = TileKeeper::tile_map.begin(); it != TileKeeper::tile_map.end(); ++it) {
    auto [_id, tile] = *it;
    CollisionDetail collision = Collision::collide_direction(tile->get_dst_rect(), dst_rect);
    if(collision.direction != CollisionDirection::NOCOLLISION) {
      in_air = true;
      switch (collision.direction)
      {
      case CollisionDirection::TOP:
        physics.vel = Vector2D(physics.vel.x, WALL_BOUNCE_VEL * Game::display->delta_T());
        physics.pos = Vector2D(physics.pos.x, collision.tile.y + TILE_H + COLLISION_BORDER_OFFSET);
        break;
      case CollisionDirection::RIGHT:
        physics.vel = Vector2D(-WALL_BOUNCE_VEL * Game::display->delta_T(), physics.vel.y);
        physics.pos = Vector2D(collision.tile.x - dst_rect.w - COLLISION_BORDER_OFFSET, physics.pos.y);
        break;
      case CollisionDirection::BOTTOM:
        physics.vel = Vector2D(physics.vel.x, 0);
        physics.pos = Vector2D(physics.pos.x, collision.tile.y - dst_rect.h);
        jumping = false;
        in_air = false;
        set_in_air = false;
        break;
      case CollisionDirection::LEFT:
        physics.vel = Vector2D(WALL_BOUNCE_VEL * Game::display->delta_T(), physics.vel.y);
        physics.pos = Vector2D(collision.tile.x + TILE_W + COLLISION_BORDER_OFFSET, physics.pos.y);
        break;
      default:
        break;
      }
    } else {
      if(set_in_air) {
        in_air = true;
      }
    }
  }

  physics.update(Game::display->delta_T());

  if(rage_left > 0) {
    rage_left--;
  }

  // todo: add interaction with other entities.
  for(auto it = Game::entities.begin(); it != Game::entities.end(); it++) {
    auto [entity_name, entity] = *it;
    if(!entity->is_used()) {
      entity->interact();
    }
  }
}

void Player::render() {
  
  // ? Can this be moved to the last part of Player::update() function ?
  // To update the SDL_Rect dst_rect with the position of the player.
  physics.sync_pos(&dst_rect);

  // Todo: Make it modular and customizable.
  // To cycle through the sprite frames.
  int sprite_frame = (int)(4 * Game::display->get_elapsed_frames() / (Game::display->get_avg_fps())) % 4;
  src_rect.x = sprite_frame * 16;

  if(rage_left > 0) {
    TextureManager::Draw(raged_player_texture, src_rect, dst_rect);
  } else {
    TextureManager::Draw(object_texture, src_rect, dst_rect);
  }
}

void Player::clean() {
  SDL_DestroyTexture(object_texture);
}

void Player::interact() {

}

void Player::powerup() {
  // todo
  // 1. Enlarge size
  // 2. Increase power_level
  if(power_level == 0) {
    power_level++;
    dst_rect.w *= 1.5;
    dst_rect.h *= 1.5;
  }
}

void Player::get_raged() {
  rage_left = (int)Game::display->get_avg_fps() * 7;
}