#include "texture_manager.h"

// STATICS ------------------------------------------------------------------------------

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src_rect, SDL_Rect dst_rect) {
  SDL_RenderCopy(Game::renderer, tex, &src_rect, &dst_rect);
}

SDL_Texture* TextureManager::load_texture(const char* texture_path) {
  SDL_Surface* tempSurface = IMG_Load(texture_path);

  if(!tempSurface) {
    std::cerr << "Error in loading the image surface" << std::endl;
    exit(1);
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

  if(!texture) {
    std::cerr << "Error in loading the image texture: " << texture_path << std::endl;
    exit(1);
  }

  SDL_FreeSurface(tempSurface);
  return texture;
}

// --------------------------------------------------------------------------------------