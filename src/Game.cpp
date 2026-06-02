#include"./include/Game.h"

bool Game::Init(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 || TTF_Init() < 0 ){
		std::cout << "Failed to init SDL, ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	font = TTF_OpenFont("./res/fonts/terminal-grotesque.ttf", 40);
	if(font == NULL){
		std::cout << "Problem loading foont, ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Could not Init SDL_Mixer, ERROR: " << Mix_GetError() << std::endl;
		return false;
	}


	hitSound = Mix_LoadWAV("./res/sfx/Hit.wav");
	if(hitSound == NULL){
		std::cout << "Could not load hitSound, ERROR: " << Mix_GetError() << std::endl;
	}


	window = SDL_CreateWindow( 
			"Bricks and Paddles",
		       	SDL_WINDOWPOS_CENTERED,
		       	SDL_WINDOWPOS_CENTERED,
		       	SCREEN_WIDTH,
		       	SCREEN_HEIGHT,
		       	SDL_WINDOW_SHOWN
		       	);
	if( window == NULL ){
		std::cout << "Failed to Create Window, ERROR: " << SDL_GetError() << std::endl;
		return false;
	} 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if( renderer == NULL ) {
		std::cout << "Failed to create renderer, ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	BackgroundTex = IMG_LoadTexture(renderer, "./res/gfx/img/BG.png");
	if ( BackgroundTex == NULL ) {
		std::cout << "Failed to Load BackgroundTex, Error: " << SDL_GetError() << std::endl;
		return false;
	}

	for(int row = 0; row < rows; row++){
		for(int col = 0; col < cols; col++) {
			Bricks brick;
			brick.Init(
				col * (brickWidth + padding) + 10,
				row * (brickHeight + padding) + 50,
				brickWidth,
				brickHeight,
				renderer
			);
			bricks.push_back(brick);
		}
	}

	ball.Init(renderer);
	paddle.Init(renderer);
  	isRunning = true;
	return true;
}

void Game::CleanUp() {
	Mix_FreeChunk(hitSound);
	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyTexture(BackgroundTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	
	SDL_Quit();
}

void Game::DrawText(const std::string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if(surface == NULL) {
		std::cout << "Failed to render text, ERROR: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == NULL) {
		std::cout << "Failed to create texture, ERROR: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(surface);
		return;
	}
	SDL_Rect destRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Game::GameOver(){
	SDL_Color Red = {255, 0, 0, 255};

	bool waiting = true;
	while(waiting) {
		SDL_SetRenderDrawColor(renderer, 0,0,0,255);
		SDL_RenderClear(renderer);
		DrawText("Game Over",SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Red);
		DrawText("Press Space to restart",SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, Red);
		SDL_RenderPresent(renderer);
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT){
				isRunning = false;
				waiting = false;
			}
			if(e.type == SDL_KEYDOWN){
				if(e.key.keysym.sym == SDLK_SPACE) {
					lost = false;
					ball.x = 400;
					ball.y = 300;
					ball.BallVelX = 0.05f;
					ball.BallVelY = 0.05f;
					bricks.clear();
					points = 0;
					paddle.PaddleX = SCREEN_WIDTH / 2 - 35;

					for(int row = 0; row < rows; row++){
						for(int col = 0; col < cols; col++) {
							Bricks brick;
							brick.Init(
								col * (brickWidth + padding) + 10,
								row * (brickHeight + padding) + 50,
								brickWidth,
								brickHeight,
								renderer
							);
							bricks.push_back(brick);
						}
					}
					waiting = false;
				}
			}
		}
	}
}

void Game::CheckCollisions() {
	//if(bottom ball is between left and right side of paddle && if )
	if(ball.x + ball.radius >= paddle.PaddleRect.x && ball.x - ball.radius <= paddle.PaddleRect.x + paddle.PaddleRect.w && ball.y + ball.radius >= paddle.PaddleRect.y && ball.y + ball.radius <= paddle.PaddleRect.y + paddle.PaddleRect.h){
		ball.y = paddle.PaddleRect.y - ball.radius;
		ball.BallVelY = -ball.BallVelY;
	}


	bool bounced = false;
	for(auto& brick : bricks) {
		if(!brick.isActive) continue;
		SDL_Rect brickrect = brick.GetRect();
		if(ball.x + ball.radius >= brickrect.x && ball.x - ball.radius <= brickrect.x + brickrect.w && ball.y + ball.radius >= brickrect.y && ball.y - ball.radius <= brickrect.y + brickrect.h) {
			brick.isActive = false;
			points++;
			if(!bounced) {
				Mix_PlayChannel(-1, hitSound, 0);
				ball.BallVelY = -ball.BallVelY;
				bounced = true;

				std::cout << points << std::endl;
				ball.BallVelY += 0.007f;
				ball.BallVelX += 0.007f;

			}
		}
	}

	if(ball.y + ball.radius >= SCREEN_HEIGHT){
		ball.BallVelY = ball.BallVelX = 0;
		lost = true;
	}
}



void Game::HandleEvent() {
	while( SDL_PollEvent( &event ) ){
		if( event.type == SDL_QUIT ){
			isRunning = false;
		}
	}
}

void Game::Draw(){
	SDL_Color white = {255, 255, 255, 255};
	SDL_RenderClear(renderer);


	SDL_Rect Background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy( renderer, BackgroundTex, NULL, &Background );

	for (auto& brick : bricks) {
	    brick.Draw(renderer);
	}

	DrawText(std::to_string(points), 10, 10, white);
	ball.Draw(renderer);
	paddle.Draw(renderer);
	SDL_RenderPresent(renderer);
};


void Game::Run(){
	while(isRunning){
		ball.Update();
		paddle.HandleInput();
		paddle.Update();
		CheckCollisions();
		HandleEvent();
		if(lost) {
			GameOver();
		}
		else {
			Draw();
		}

	}
}
