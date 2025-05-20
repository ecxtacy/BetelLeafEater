#pragma once
#include <vector>
#include <utility>
#include <structs.h>

/* Interface/Abstract class representing any game object which is not the player. */
class GameEntity {
  public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handle_events(SDL_Event* event) = 0;
    virtual void clean() = 0;

    virtual void interact() = 0;

    virtual bool is_used() = 0;

    virtual std::vector<struct Point> get_bounding_rect() = 0;
};