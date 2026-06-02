
## How to run:
Make sure you have a build/ folder and SDL2 installed  

Build using g++: ``` g++ src/main.cpp src/Game.cpp src/Bricks.cpp src/Ball.cpp -o build/game -std=c++17 $(sdl2-config --cflags) $(sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf ```     
Run using: ``` ./build/game ```   