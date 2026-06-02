#include"./include/Ball.h"

void Ball::Init(SDL_Renderer* renderer){
	BallTex = IMG_LoadTexture(renderer, "./res/gfx/img/Ball.png");
	if(BallTex == NULL){
		std::cout << "problem loading BallTex, ERROR: " << SDL_GetError() << std::endl;
	}
}


void Ball::Update() {
	x += BallVelX;
	y += BallVelY;

	if( x - radius <= 0 || x + radius >= SCREEN_WIDTH) {
		BallVelX = -BallVelX;
	}

	if( y - radius <= 0 || y + radius >= SCREEN_HEIGHT ){
		BallVelY = -BallVelY;
	}
}

void Ball::Draw( SDL_Renderer* renderer) {
	SDL_Rect ballRect = {
		(int)x - radius,
		(int)y - radius,
		radius * 2,
		radius * 2
	};
	SDL_RenderCopy(renderer, BallTex, NULL, &ballRect);
}


void Ball::DrawCircle( SDL_Renderer* renderer, int cx, int cy, int radius ) {
	for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

