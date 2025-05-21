#pragma once

#include "vector2D.h"
#include "SDL2/SDL.h"

class PhysicsComponent {
  public:
    PhysicsComponent();
    ~PhysicsComponent();

    Vector2D pos;
    Vector2D vel;
    Vector2D acc;

    void update(float delta_time);
    Vector2D get_pos();

    void accelerate_x(float ax);
    void accelerate_y(float ay);

    void move_x(float dx);
    void move_y(float dy);

    void sync_pos(SDL_Rect* dst_rect);

    void log(const char* title);

    void toggle_gravity();
    void apply_gravity();
    void remove_gravity();
    
    void update_friction(float);

  private:

    bool gravity;
    float grav_acc;
    float friction;
};