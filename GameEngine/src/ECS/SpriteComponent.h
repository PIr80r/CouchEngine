#pragma once
#include "Components.h"
#include "SDL.h"
#include "../textureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	
	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 2, 500);
		Animation walk = Animation(1, 2, 100);
		Animation dash = Animation(2, 2, 100);
		Animation crouch = Animation(3, 0, 0);
		Animation Lpunch = Animation(4, 0, 0);
		Animation Mpunch = Animation(5, 0, 0);
		Animation Hpunch = Animation(6, 0, 0);
		Animation Grab = Animation(7, 0, 0);
		Animation Lkick = Animation(8, 0, 0);
		Animation Mkick = Animation(9, 0, 0);
		Animation Hkick = Animation(10, 0, 0);
		Animation Stand = Animation(11, 0, 0);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk)
		animations.emplace("Dash", dash);
		animations.emplace("Crouch", crouch);
		animations.emplace("Lpunch", Lpunch);
		animations.emplace("Mpunch", Mpunch);
		animations.emplace("Hpunch", Hpunch);
		animations.emplace("Grab", Grab);
		animations.emplace("Lkick", Lkick);
		animations.emplace("Mkick", Mkick);
		animations.emplace("Hkick", Hkick);
		animations.emplace("Stand", Stand);

		Play("Idle");

		setTex(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = textureManager::loadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override
	{
		textureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};