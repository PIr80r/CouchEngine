#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "SDL.h"

class KeyboardReader : public Component
{

public:
	TimerComponent timer;
	int length;
	const Uint8* keystate;
	Uint8 *oldKeystate;
	Uint32 elapsed, current,windowT;
	bool test;

	void init() override
	{
		timer = TimerComponent();
		elapsed = 0u;
		windowT = 150u;
		current = 0u;
		keystate = SDL_GetKeyboardState(&length);
		oldKeystate = new Uint8[length];
	}

	void inputRefresh()
	{
		keystate = SDL_GetKeyboardState(&length);
		memcpy(oldKeystate, keystate, length);
	}

	Uint32 timeTrue(bool test)
	{
		timer.start();
		while (test)
		{
			elapsed = timer.elapsed();
		}
		return elapsed;
	}
	
	Uint32 timeFalse(bool test)
	{
		timer.start();
		while (!test)
		{
			elapsed = timer.elapsed();
		}
		return elapsed;
	}

	void clearTime()
	{
		timer.stop();
		elapsed = 0u;
	}

	bool keyDown(ConfigKeys::Keyboard scancode)
	{
		return keystate[scancode];
	}
	
	bool keyDown(SDL_Scancode scancode)
	{
		return keystate[scancode];
	}

	bool keyPressed(ConfigKeys::Keyboard scancode)
	{
		return !oldKeystate[scancode] && keystate[scancode];
	}
	
	bool keyPressed(SDL_Scancode scancode)
	{
		return !oldKeystate[scancode] && keystate[scancode];
	}
	
	bool keyReleased(ConfigKeys::Keyboard scancode)
	{
		return oldKeystate[scancode] && !keystate[scancode];
	}

	bool keyReleased(SDL_Scancode scancode)
	{
		return oldKeystate[scancode] && !keystate[scancode];
	}

	void update() override
	{
		
		inputRefresh();
	}
};