#include "physics.h"
#include <iostream>
#include "defs.h"

PhysicsComponent::PhysicsComponent() 
{
  gravity = false;

  // todo: Change this properly later.
  grav_acc = GRAV_ACC;
  friction = 0;
};

PhysicsComponent::~PhysicsComponent() 
{};

void PhysicsComponent::accelerate_x(float ax) 
{
  vel += Vector2D(ax, 0);
};

void PhysicsComponent::accelerate_y(float ay) 
{
  vel += Vector2D(0, ay);
};

void PhysicsComponent::move_x(float dx) 
{
  pos += Vector2D(dx, 0);
};

void PhysicsComponent::move_y(float dy) 
{
  pos += Vector2D(0, dy);
};

void PhysicsComponent::sync_pos(SDL_Rect* dst_rect) {
  dst_rect->x = pos.x;
  dst_rect->y = pos.y;  
}

void PhysicsComponent::log(const char* title)
{
  std::cout << "------------ LOG FOR " << title << std::endl;
  std::cout << "Gravity: " << (gravity ? "yes" : "no") << std::endl;
  std::cout << "position: " << pos << std::endl;
  std::cout << "velocity: " << vel << std::endl;
  std::cout << "acceleration: " << acc << std::endl << std::endl;
};

void PhysicsComponent::update_friction(float f) {
  friction = f;
}

void PhysicsComponent::apply_gravity() {
  gravity = true;
}

void PhysicsComponent::remove_gravity() {
  gravity = false;
}

void PhysicsComponent::update(float delta_time)
{
  if(gravity) {
    acc = Vector2D(acc.x, (grav_acc / 1000.0) * FRAME_DELAY * delta_time);
  } else {
    acc = Vector2D(acc.x, 0);
  }

  // Apply friction.
  vel += Vector2D((-vel.x) * friction * delta_time, 0);

  // Accelerate
  vel += acc;

  // Clamp the velocity magnitude in range [0, MAX_X_VELOCITY], [0, MAX_Y_VELOCITY]
  if(std::abs(vel.x) <= 1e-4) vel.x = 0;
  if(std::abs(vel.y) <= 1e-4) vel.y = 0;
  int dirx = (vel.x / std::abs(vel.x)), diry = (vel.y / std::abs(vel.y));
  if(std::abs(vel.x) > MAX_X_VELOCITY) vel.x = dirx * MAX_X_VELOCITY;
  if(std::abs(vel.y) > MAX_Y_VELOCITY) vel.y = diry * MAX_Y_VELOCITY;
  
  // Update position
  pos += vel;

};

void PhysicsComponent::toggle_gravity()
{
  gravity ^= 1;
};

Vector2D PhysicsComponent::get_pos() 
{
  return pos;
};