#include "display.h"
#include "defs.h"
#include <iomanip>

ScreenDisplay::ScreenDisplay(const char* title, int x, int y, int screen_h, int screen_w, int fps) {
  display_height = screen_h;
  display_width = screen_w;

  FPS = fps;

  xpos = x;
  ypos = y;

  window_title = title;
  frames_elapsed = 0;

  game_start_time = SDL_GetTicks();
}

SDL_Window* ScreenDisplay::init_window(bool fullscreen) {
  Uint32 flags = (SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
  SDL_Window* window = SDL_CreateWindow(window_title, xpos, ypos, display_width, display_height, flags);

  if(!window) {
    std::cerr << "Error in creating the window" << std::endl;
    exit(1);
  }

  return window;
}

int ScreenDisplay::fps() 
{
  return FPS;
}

int ScreenDisplay::width() 
{
  return display_width;
}

int ScreenDisplay::height() 
{
  return display_height;
}

float ScreenDisplay::get_avg_fps() 
{
  return ScreenDisplay::avg_fps;
}

void ScreenDisplay::set_avg_fps(float mean_fps) 
{
  ScreenDisplay::avg_fps = mean_fps;
}

float ScreenDisplay::delta_T() 
{
  return 60.0/avg_fps;
}

void ScreenDisplay::count_frame() 
{
  frames_elapsed++;
  set_avg_fps((1000.0 * get_elapsed_frames()) / (1.0*SDL_GetTicks() - game_start_time));
  if(PRINT_AVG_FPS) print_avg_fps();
}

int ScreenDisplay::get_elapsed_frames() 
{
  return frames_elapsed;
}

void ScreenDisplay::print_avg_fps() 
{
  std::cout << "Average FPS: " << std::setprecision(4) << get_avg_fps()  << std::endl;
}