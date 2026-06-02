#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Paddle {
public:
	void Init(SDL_Renderer* renderer);
	void HandleInput();
	void Draw(SDL_Renderer* renderer);
	void Update();

	SDL_Rect PaddleRect;
	float PaddleX = 0.0f;
private:

	const float PaddleVel = 0.1f;

	SDL_Texture* PaddleTex = NULL;
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

};