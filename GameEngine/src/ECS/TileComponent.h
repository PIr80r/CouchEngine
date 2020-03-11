#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	SDL_Rect tileRect;
	int tileID;

	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "Assets/Bg1.png";
			break;
		case 1:
			path = "Assets/Bg2.png";
			break;
		case 2:
			path = "Assets/Bg3.png";
			break;
		default:
			break;
		}
	}
	void init()
	{
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};