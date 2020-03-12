#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "SDL.h"
#include "SDL_mixer.h"

class KeyboardController : public Component
{

public:
	TransformComponent *transform;
	SpriteComponent *sprite;
	int length;
	const Uint8* keystate;
	Uint8 *firstInput;
	Uint8* secondInput;
	Uint8* thirdInput;
	Uint8* fourthInput;
	Mix_Chunk *Nice = NULL;

	enum keys {
		Jump = SDL_SCANCODE_W,
		Left = SDL_SCANCODE_A, 
		Right = SDL_SCANCODE_D,
		Crouch = SDL_SCANCODE_S,
		lPunch = SDL_SCANCODE_J,
		mPunch = SDL_SCANCODE_K,
		HPunch = SDL_SCANCODE_L,
		lKick = SDL_SCANCODE_N,
		mKick = SDL_SCANCODE_M,
		hKick = SDL_SCANCODE_COMMA,
	};

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		keystate = SDL_GetKeyboardState(&length);
		firstInput = new Uint8[length];
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		Nice = Mix_LoadWAV("Assets/nice.wav");
	}

	void update() override
	{
		if (keystate[SDL_SCANCODE_SPACE])
		{	
			if (Mix_Playing(0) == 0) {
				Mix_PlayChannel(0, Nice, 0);
			}
		}
		if (keystate[Jump])
		{
			transform->velocity.y = -1;
		}
		if (keystate[Crouch])
		{
			std::cout << "Crouch\n";
		}
		if (keystate[Left])
		{
			transform->velocity.x = -1;
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
		}
		if (keystate[Left] && !secondInput[Left] && firstInput[Left])
		{
			transform->velocity.x = -2;
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
		}
		if (keystate[Right])
		{
			transform->velocity.x = 1;
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		if (keystate[Right] && !secondInput[Right] && firstInput[Right])
		{
			transform->velocity.x = 2;
			sprite->spriteFlip = SDL_FLIP_NONE;
		}
		if (!keystate[Jump] && !keystate[Crouch])
		{
			transform->velocity.y = 0;
		}
		if (!keystate[Left] && !keystate[Right])
		{
			transform->velocity.x = 0;
		}
		if (transform->velocity.x > 0 || transform->velocity.x < 0 || transform->velocity.y > 0 || transform->velocity.y < 0)
		{
			sprite->Play("Walk");
		}
		else
		{
			sprite->Play("Idle");
		}
		SDL_PumpEvents();
		std::memcpy(firstInput, keystate, length);
		std::memcpy(secondInput, keystate, length);
		std::memcpy(thirdInput, keystate, length);
		std::memcpy(fourthInput, keystate, length);
		keystate = SDL_GetKeyboardState(&length);
	}
};