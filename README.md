
## How to run:
Make sure you have a build/ folder and SDL2 installed  

Build using g++: ``` g++ src/main.cpp src/Game.cpp src/Bricks.cpp src/Ball.cpp -o build/game -std=c++17 $(sdl2-config --cflags) $(sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf ```     
Run using: ``` ./build/game ```   

flowchart TD
A[Ask a Question]-->B[Do backgrounf research]
B-->C[form hypo]
C-->D[Test with experiment]
D-->E[analyze data]
E-->F[does data spport hypo]
F--Yes-->G[share]
F--No-->H[revise]
H-->D
