#pragma once
#include "Game.h"

class textureManager
{
public:
	static SDL_Texture* loadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};