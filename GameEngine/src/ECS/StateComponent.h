#pragma once

#include "Components.h"
#include "SpriteComponent.h"
#include "SDL.h"

class StateComponent : public Component
{
public:
	bool walking,jumping,dashing;
	TimerComponent counter;
	
	StateComponent() = default;

	StateComponent(bool r) {
		walking = r;
		jumping = r;
		dashing = r;
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