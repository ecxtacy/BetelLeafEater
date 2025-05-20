#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <iostream>

struct ColorRGBA {
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
};

enum Colors {
  COLOR_WHITE,
  COLOR_BLACK,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_YELLOW,
};

struct Point {
  int x;
  int y;
};