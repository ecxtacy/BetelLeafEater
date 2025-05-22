#pragma once
#include "SDL2/SDL.h"
#include <vector>
#include <utility>
#include "../abstract/entity.h"
#include "../components/physics.h"

/**
 * @class Player
 * @brief Player (Main Game Object), all functions and attributes defined out.
 */
class Player {
  public:

    /* Initialize the object, load the textures. Provide different textures for different costumes/looks. */
    Player(const char* texture_path, const char* raged_texture_path);
    ~Player();

    /// Setters

    void set_texture_portion(SDL_Rect srect);
    void set_dimensions(int w, int h);
    void set_position(float x, float y);
    void set_velocity(float vx, float vy);
    void set_gravitational_object(bool is_grav_obj);

    bool is_used();

    std::vector<struct Point> get_bounding_rect(); 

    void handle_events(SDL_Event* event);
    void update();
    void render();
    void clean();

    void interact();

    // Player specific functions.

    void powerup();
    void get_raged();
  
  private:
    SDL_Texture* object_texture;
    SDL_Texture* raged_player_texture;
    SDL_Rect src_rect, dst_rect;

    // Player attributes.
    int power_level;
    int rage_left;

    // To simulate physics on this object.
    PhysicsComponent physics;

    // These are taken care by PhysicsComponent
    float vel_x, vel_y;
    float pos_x, pos_y;
    float acc_x, acc_y;

    // apply_gravity taken care by physics component
    bool apply_gravity;

    // To keep track of player state.
    bool in_air;
    bool jumping;

};