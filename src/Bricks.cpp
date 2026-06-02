#include"./include/Bricks.h"

void Bricks::Init(int x, int y, int width, int height,SDL_Renderer* renderer ){
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	isActive = true;
	BrickTex = IMG_LoadTexture(renderer, "./res/gfx/img/Brick.png");
	if(BrickTex == NULL){
		std::cout << "Failed to load BrickTex, ERROR: " << SDL_GetError() << std::endl;
	}
}

void Bricks::Draw(SDL_Renderer* renderer) {
	if(!isActive) return;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderCopy(renderer, BrickTex, NULL, &rect);
}

SDL_Rect Bricks::GetRect() {
	return rect;
}