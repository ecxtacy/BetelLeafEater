#include "collision.h"

/**
 * @returns CollisionDetail
 * 
 * @param SDL_Rect b
 * @param SDL_Rect a
 * 
 * @brief Checks the details how SDL_Rect a is colliding with SDL_Rect b,
 * or reports no collision.
 * 
 * First checks what point of SDL_Rect a is colliding with SDL_Rect b,
 * then returns a CollisionDetail struct with the information regarding
 * direction and SDL_Rect b.
 */
CollisionDetail Collision::collide_direction(SDL_Rect b, SDL_Rect a) {

  /**
   * Supposing SDL_Rect forms a rectangle, point_id indicates which
   * vertex of the rectangle has collided. is the colliding point
   * top-left: 0
   * top-right: 1
   * bottom-left: 2
   * bottom-right: 3
   */
  int point_id = 0;

  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      int px = b.x + (j * b.w);
      int py = b.y + (i * b.h);

      if(a.x <= px && px <= a.x + a.w && a.y <= py && py <= a.y + a.h) {
        switch (point_id)
        {
        case 0:
          if(std::abs(px - (a.x + a.w)) >= std::abs(py - (a.y + a.h))) {
            return {BOTTOM, b};
          } else {
            return {RIGHT, b};
          }
          break;

        case 1:
          if(std::abs(px - (a.x)) >= std::abs(py - (a.y + a.h))) {
            return {BOTTOM, b};
          } else {
            return {LEFT, b};
          }
          break;

        case 2:
          if(std::abs(px - (a.x + a.w)) >= std::abs(py - (a.y))) {
            return {TOP, b};
          } else {
            return {RIGHT, b};
          }
          break;

        case 3:
          if(std::abs(px - (a.x)) >= std::abs(py - (a.y))) {
            return {TOP, b};
          } else {
            return {LEFT, b};
          }
          break;

        default:
          break;
        }
        break;
      }

      point_id++;
    }
  }

  return {NOCOLLISION, b};
}