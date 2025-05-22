#pragma once
#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "game.h"

/**
 * @class TextureManager
 * @brief Utility for handling loading and rendering of textures on the screen.
 * 
 * Textures are the data loaded in GPU VRAM. 
 * First a Surface is constructed out of an image, surface resides in the RAM. Then texture is created out of the surface.
 */
class TextureManager {
  public:

    /* Load image and create its texture from specified image file path. */
    static SDL_Texture* load_texture(const char* texture);

    /* Render the image texture to the screen. */
    static void Draw(SDL_Texture* tex, SDL_Rect src_rect, SDL_Rect dst_rect);
};