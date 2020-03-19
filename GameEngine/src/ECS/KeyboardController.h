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
	StateComponent *state;
	TimerComponent timer;
	int length;
	const Uint8* keystate;
	Uint8 *oldKeystate;
	Uint32 elapsed, current;
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
		state = &entity->getComponent<StateComponent>();
		timer = TimerComponent();
		elapsed = 0u;
		Uint32 current = 0u;
		keystate = SDL_GetKeyboardState(&length);
		oldKeystate = new Uint8[length];
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		timer.start();
		Nice = Mix_LoadWAV("Assets/nice.wav");
	}

	void update() override
	{
		elapsed = timer.elapsed();
		
		if (keystate[SDL_SCANCODE_SPACE])
		{	
			if (Mix_Playing(0) == 0) {
				Mix_PlayChannel(0, Nice, 0);
			}
		}
		if (keystate[Jump])
		{
			std::cout << "Jump\n";
			state->jumping = true;
		}
		if (keystate[Crouch])
		{
			std::cout << "Crouch\n";
		}
		if (keystate[Left])
		{
			sprite->Play("Walk");
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			transform->velocity.x = -1;
			
		}
		if (keystate[Left] && !oldKeystate[Left] && !state->checkTimeFalse(state->walking, 500u))
		{
			transform->velocity.x = -5;
			std::cout << "Dashing\n";
		}
		if (keystate[Right])
		{
			sprite->Play("Walk");
			sprite->spriteFlip = SDL_FLIP_NONE;
			transform->velocity.x = 1;
		}
		if (keystate[Right] && !oldKeystate[Right] && !state->checkTimeFalse(state->walking, 500u))
		{
			transform->velocity.x = 5;
			std::cout << "Dashing\n";
		}
		
		/*if (keystate[Right] && !secondInput[Right] && firstInput[Right])
		{
			sprite->Play("Walk");
			transform->velocity.x = 5;
			std::cout << "Dashing\n";
			sprite->spriteFlip = SDL_FLIP_NONE;
		}*/
		if (!keystate[Jump] && !keystate[Crouch])
		{
			state->jumping = false;
		}
		if (!keystate[Left] && !keystate[Right])
		{
			transform->velocity.x = 0;
		}
		if (transform->velocity.x > 0 || transform->velocity.x < 0)
		{
			state->walking = true;
		}
		if (transform->velocity.x == 0)
		{
			current = timer.getTicks();
			sprite->Play("Idle");
			state->walking = false;
		}
		std::cout << elapsed / 1000u << std::endl;
		std::memcpy(oldKeystate, keystate, length);
		SDL_PumpEvents();
		keystate = SDL_GetKeyboardState(&length);
	}
};