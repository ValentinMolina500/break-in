game:
	g++  -std=c++11 main.cpp ball.cpp texture.cpp player.cpp helpers.cpp block.cpp timer.cpp -o play -I include -L lib -lSDL2-2.0.0 -lSDL2_image-2.0.0 -lSDL2_ttf-2.0.0 