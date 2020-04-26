#pragma once
#include <SDL.h>

class ConfigKeys
{
public:
	enum Keyboard {
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
};