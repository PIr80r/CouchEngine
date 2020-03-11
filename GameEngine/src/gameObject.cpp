#include "gameObject.h"
#include "textureManager.h"

gameObject::gameObject(const char* texSheet, int x, int y)
{
	objTexture = textureManager::loadTexture(texSheet);

	xpos = x;
	ypos = y;
}

void gameObject::Update()
{
	
	xpos++;
	ypos++;
	
	srcRect.w = 180;
	srcRect.h = 180;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 1;
	destRect.h = srcRect.h * 1;
}

void gameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}