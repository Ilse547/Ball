#pragma once
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

class Bricks {
public:
	bool isActive = true;
	void Init(int x, int y, int width, int height, SDL_Renderer* renderer);
	void Draw(SDL_Renderer* renderer);
	SDL_Rect GetRect();

private:
	SDL_Rect rect;
	SDL_Texture* BrickTex = NULL;
};