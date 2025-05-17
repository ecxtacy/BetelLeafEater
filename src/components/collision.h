#pragma once
#include "SDL2/SDL.h"

/**
 * @enum CollisionDirection
 * To specify which direction the collision has occurred on.
 */
enum CollisionDirection {
  NOCOLLISION = -1,
  TOP,
  RIGHT,
  BOTTOM,
  LEFT,
};

/**
 * @struct CollisionDetail
 * @brief Details regarding how the sprite has collided with the tile.
 * Contains the direction of collision, and the tile on which collision has occurred.
 */
struct CollisionDetail {
  CollisionDirection direction;
  SDL_Rect tile;
};

/**
 * @class Collision
 * Provides functions and utilities to check collision among different game objects.
 */
class Collision {
  public:

    // Check from which direction a is colliding with b.
    // TOP, RIGHT, BOTTOM, UP -> 0, 1, 2, 3
    // Returns -1 (NOCOLLISION) if no collision
    static CollisionDetail collide_direction(SDL_Rect b, SDL_Rect a);
  private:
};