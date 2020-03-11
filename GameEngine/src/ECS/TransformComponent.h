#pragma once

#include "Components.h"
#include "../Vector2D.h"

struct TransformComponent : public Component
{
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1.0f;

	int speed = 3;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float sc)
	{
		position.Zero();

		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h,  float s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};