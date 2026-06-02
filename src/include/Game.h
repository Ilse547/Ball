#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cmath>


#include "Bricks.h"
#include "Ball.h"
#include "Paddle.h"


class Game {
public:
	SDL_Renderer* renderer = NULL;
	bool Init();
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	void CleanUp();
	void Draw();
	void HandleEvent();
	void Run();
	void CheckCollisions();
	bool lost = false;
	void GameOver();
	void DrawText(const std::string& text, int x, int y, SDL_Color color);
	Ball ball;
	Paddle paddle;
private:
	SDL_Window* window = NULL;
	bool success;
	SDL_Event event;
	bool isRunning;
	SDL_Texture* BackgroundTex = NULL;
	std::vector<Bricks> bricks;
	TTF_Font* font = NULL;

	Mix_Chunk* hitSound = NULL;

    int points = 0;
    int brickWidth = 75;
	int brickHeight = 30;
	int cols = 10;
	int rows = 4;
	int padding = 5;


};
