#pragma once
#include "Game.h"

class gameObject
{

public:

	gameObject(const char* texSheet, int x, int y);

	~gameObject();

	void Update();
	void Render();

private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};