#pragma once
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<iostream>

class Ball {
public:
	void Update();
	void DrawCircle( SDL_Renderer* renderer, int cx, int cy, int radius );
	void Draw(SDL_Renderer* renderer);
	void Init( SDL_Renderer* renderer );


	float BallVelX = 0.05f;
	float BallVelY = 0.05f;
	float x = 400.0f;
	float y = 300.0f;
	int radius = 20;

private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    SDL_Texture* BallTex = NULL;
};