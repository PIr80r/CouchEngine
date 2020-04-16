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
	CharacterComponent *chr;
	StateComponent *state;
	TimerComponent timer;
	int length;
	const Uint8* keystate;
	Uint8 *oldKeystate;
	Uint32 elapsed, current,windowT;
	Mix_Chunk *Nice = NULL;
	bool test;


	

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
		chr = &entity->getComponent<CharacterComponent>();
		timer = TimerComponent();
		elapsed = 0u;
		windowT = 150u;
		Uint32 current = 0u;
		keystate = SDL_GetKeyboardState(&length);
		oldKeystate = new Uint8[length];
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		timer.start();
		Nice = Mix_LoadWAV("Assets/nice.wav");
	}

	void inputRefresh()
	{
		keystate = SDL_GetKeyboardState(&length);
		memcpy(oldKeystate, keystate, length);
	}

	bool keyDown(KeyboardController::keys scancode)
	{
		return keystate[scancode];
	}
	
	bool keyDown(SDL_Scancode scancode)
	{
		return keystate[scancode];
	}

	bool keyPressed(KeyboardController::keys scancode)
	{
		return !oldKeystate[scancode] && keystate[scancode];
	}
	
	bool keyPressed(SDL_Scancode scancode)
	{
		return !oldKeystate[scancode] && keystate[scancode];
	}
	
	bool keyReleased(KeyboardController::keys scancode)
	{
		return oldKeystate[scancode] && !keystate[scancode];
	}

	bool keyReleased(SDL_Scancode scancode)
	{
		return oldKeystate[scancode] && !keystate[scancode];
	}

	void update() override
	{
		elapsed = timer.elapsed();

		if (keyPressed(SDL_SCANCODE_SPACE))
		{	
			if (Mix_Playing(0) == 0) {
				Mix_PlayChannel(0, Nice, 0);
			}
		}
		if (keyDown(Jump))
		{
			std::cout << "Jump\n";
			state->jumping = true;
		}
		if (keyReleased(Jump))
		{
			std::cout << "Falling\n";
			state->jumping = false;
		}
		if (keyDown(Crouch))
		{
			std::cout << "Crouching\n";
		}
		if (keyDown(Left))
		{
			sprite->Play("Walk");
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			cout << "walking left\n";
			if(state->walking == false)
			{
				transform->velocity.x = -1 * chr->speed;
				state->walking = true;
			}
			if (test)
			{
				state->dashing = true;
				cout << "Dashing\n";
				transform->velocity.x = -2 * chr->speed;
			}
		}
		
		if (keyDown(Right))
		{
			sprite->Play("Walk");
			cout << "Walking right\n";
			sprite->spriteFlip = SDL_FLIP_NONE;
			
			if (state->walking == false)
			{
				transform->velocity.x = 1 * chr->speed;
				state->walking = true;
			}
			if (test)
			{
				state->dashing = true;
				cout << "Dashing\n";
				transform->velocity.x = 2 * chr->speed;
			}
		}
		if (keyReleased(Left) || keyReleased(Right))
		{
			sprite->Play("Idle");
			transform->velocity.x = 0;
			if (state->walking == true)
			{
				test = state->checkTimeTrue(state->walking, windowT);
			}
			if (state->checkTimeTrue(state->walking, windowT + 1u))
			{
				test = false;
				state->walking = false;
				state->dashing = false;
			}
		}
		
		std::cout << elapsed / 1000u << std::endl;
		inputRefresh();
	}
};