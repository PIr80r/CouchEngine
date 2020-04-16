#pragma once
#include "Components.h"
#include "SpriteComponent.h"
#include "SDL.h"

using namespace std;

struct CharacterComponent : public Component
{
	SpriteComponent *sprite;
	
	string selected;
	int health, speed;

	CharacterComponent() = default;

	CharacterComponent(string character) {
		selected = character;
	}


	void init() override
	{
		sprite = &entity->getComponent<SpriteComponent>();

		if (selected == "Cheezybun")
		{
			health = 100;
			speed = 3;
			Animation doublekick = Animation(12, 0, 0);
			sprite->animations.emplace("Double Kick", doublekick);
		}
		else {
			health = 100;
			speed = 1;
		}
	}
};