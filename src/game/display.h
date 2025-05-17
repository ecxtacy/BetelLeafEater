#pragma once
#include "SDL2/SDL.h"
#include <iostream>

class ScreenDisplay {
  public:

    /* Initialize the screen display. */
    ScreenDisplay(const char* title, int x, int y, int display_h, int display_w, int fps);
    ~ScreenDisplay();

    int width();
    int height();
    int fps();

    /* Keep record of the FPS in the game. */
    float get_avg_fps();
    void set_avg_fps(float mean_fps);
    
    /* 
      To make the game movements consistent between different frame-rates 
      and remove frame-rate dependency, this metric is used. 
      Ref: https://drewcampbell92.medium.com/understanding-delta-time-b53bf4781a03
    */
    float delta_T();
    
    /* Count the next frame and update the stats. */
    void count_frame();

    int get_elapsed_frames();
    void print_avg_fps();

    /* Initialize the SDL window object. */
    SDL_Window* init_window(bool fullscreen);

  private:
    
    // Screen dimensions.
    int display_width, display_height;
    
    // Ideally set FPS.
    int FPS;
    
    // Screen position.
    int xpos, ypos;

    // Screen stats.
    float avg_fps;
    int frames_elapsed;
    
    Uint32 game_start_time;

    // Title of the game window.
    const char* window_title;
};
