#ifndef __VBALL__
#define __VBALL__

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>
#include <vector>

#include "texture.h"
#include "player.h"
#include "block.h"
#include "helpers.h"

class Ball
{
     public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 10;
		static const int DOT_HEIGHT = 10;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 3;
        float current_speed;
        LTexture ball_texture;

		//Initializes the variables
		Ball(int x, int y);

		//Moves the dot and check collision against tiles
		void move(float time_step, Player &player, std::vector<Block>& blocks);

		
        void load_texture();

		// Shows the dot on the screen
		void render();

        FRect get_bbox() { return mBox; }

    private:
		//Collision box of the dot
		FRect mBox;
        float mPosX, mPosY;
		//The velocity of the dot
		float mVelX, mVelY;
};
#endif