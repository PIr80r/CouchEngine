#pragma once
#include "Components.h"
#include "SpriteComponent.h"
#include "SDL.h"

class StateComponent : public Component
{
public:
	bool walking;
	bool jumping;
	TimerComponent counter;
	
	StateComponent() = default;

	StateComponent(bool r) {
		walking = r;
		jumping = r;
	}

	bool checkTimeFalse(bool cond, Uint32 ms)
	{
			counter.start();
			while (!cond)
			{
				if (SDL_GetTicks() >= ms + counter.getTicks())
				{
					return true;
				}
				else if (SDL_GetTicks() < ms + counter.getTicks())
				{
					return false;
				}

			}
	}

	bool checkTimeTrue(bool cond, Uint32 ms)
	{
		counter.start();
		while (cond)
		{
			if (SDL_GetTicks() >= ms + counter.getTicks())
			{
				return true;
			}
			else if (SDL_GetTicks() < ms + counter.getTicks())
			{
				return false;
			}

		}
	}
	
	void init() override
	{
		walking = false;
		jumping = false;
	}
	void update() override
	{
			
	}
};