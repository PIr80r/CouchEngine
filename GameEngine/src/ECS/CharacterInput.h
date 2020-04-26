#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "SDL.h"
#include "SDL_mixer.h"

class CharacterInput : public Component
{

public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	CharacterComponent* chr;
	StateComponent* state;
	KeyboardReader* keyboard;
	TimerComponent timer;
	Uint32 elapsed, current, windowT;
	Mix_Chunk* Nice = NULL;
	bool test;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		state = &entity->getComponent<StateComponent>();
		chr = &entity->getComponent<CharacterComponent>();
		keyboard = &entity->getComponent<KeyboardReader>();
		timer = TimerComponent();
		elapsed = 0u;
		windowT = 150u;
		Uint32 current = 0u;
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		timer.start();
		Nice = Mix_LoadWAV("Assets/nice.wav");
	}

	void update() override
	{
		elapsed = timer.elapsed();

		if (keyboard->keyPressed(SDL_SCANCODE_SPACE))
		{
			if (Mix_Playing(0) == 0) {
				Mix_PlayChannel(0, Nice, 0);
			}
		}
		if (keyboard->keyDown(ConfigKeys::Keyboard::Jump))
		{
			std::cout << "Jump\n";
			state->jumping = true;
		}
		if (keyboard->keyReleased(ConfigKeys::Keyboard::Jump))
		{
			std::cout << "Falling\n";
			state->jumping = false;
		}
		if (keyboard->keyDown(ConfigKeys::Keyboard::Crouch))
		{
			std::cout << "Crouching\n";
		}
		if (keyboard->keyDown(ConfigKeys::Keyboard::Left))
		{
			sprite->Play("Walk");
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			cout << "walking left\n";
			if (state->walking == false)
			{
				transform->velocity.x = -1 * chr->speed;
				state->walking = true;
			}
		}

		if (keyboard->keyDown(ConfigKeys::Keyboard::Left) && test)
		{
			state->dashing = true;
			cout << "Dashing\n";
			transform->velocity.x = -2 * chr->speed;
		}

		if (keyboard->keyDown(ConfigKeys::Keyboard::Right))
		{
			sprite->Play("Walk");
			cout << "Walking right\n";
			sprite->spriteFlip = SDL_FLIP_NONE;

			if (state->walking == false)
			{
				transform->velocity.x = 1 * chr->speed;
				state->walking = true;
			}
		}
		if (keyboard->keyDown(ConfigKeys::Keyboard::Right) && test)
		{
			state->dashing = true;
			cout << "Dashing\n";
			transform->velocity.x = 2 * chr->speed;
		}
		if (keyboard->keyReleased(ConfigKeys::Keyboard::Left) && keyboard->keyReleased(ConfigKeys::Keyboard::Right))
		{
			sprite->Play("Idle");
			transform->velocity.x = 0;
			if (keyboard->timeTrue(state->walking) > windowT)
			{
				test = false;
				state->walking = false;
				state->dashing = false;
			}
			if (keyboard->timeTrue(state->walking) <= windowT)
			{
				test = true;
			}
		}

		std::cout << elapsed / 1000u << std::endl;
	}
};