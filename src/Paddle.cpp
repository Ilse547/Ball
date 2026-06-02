#include "./include/Paddle.h"

void Paddle::Init(SDL_Renderer* renderer) {
	PaddleTex = IMG_LoadTexture(renderer, "./res/gfx/img/Paddle.png");
	if(PaddleTex == NULL) {
		std::cout << "Failed to load PaddleTex, ERROR: " << SDL_GetError() << std::endl;
	}
	PaddleX = SCREEN_WIDTH / 2 - 35;
	PaddleRect.x = (int)PaddleX;
	PaddleRect.y = SCREEN_HEIGHT - 20;
	PaddleRect.w = 70;
	PaddleRect.h = 10;

}

void Paddle::HandleInput() {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if(keystate[SDL_SCANCODE_A]) PaddleX -= PaddleVel;
	if(keystate[SDL_SCANCODE_D]) PaddleX += PaddleVel;
	PaddleRect.x = (int)PaddleX;
}

void Paddle::Update() {
	if(PaddleX < 0) PaddleX = 0;
	if(PaddleX + PaddleRect.w > SCREEN_WIDTH) PaddleX = SCREEN_WIDTH - PaddleRect.w;
}

void Paddle::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, PaddleTex, NULL, &PaddleRect);
}