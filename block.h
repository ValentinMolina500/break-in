#ifndef __VBLOCK__
#define __VBLOCK__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "player.h"
#include "helpers.h"
class Block
{
     public:
		//The dimensions of the dot
		static const int BLOCK_WIDTH = 40;
		static const int BLOCK_HEIGHT = 40;

        bool is_dead;

		//Initializes the variables
		Block(int x, int y);

		// Shows the dot on the screen
		void render();

        FRect get_bbox() { return m_box; }

        float get_width() { return m_box.w; }

        // KILL the block
        void kill();

    private:
		//Collision box of the dot
		FRect m_box;
};
#endif