#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"./include/Game.h"

int main( int argc, char* args[] ) {
	Game game;

	
	if( game.Init() ) {
		game.Run();
	}


	game.CleanUp();
	return 0;
}
