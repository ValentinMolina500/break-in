#ifndef __VGLOBALS__
#define __VGLOBALS__
#include <SDL2/SDL.h>
#include "texture.h"

extern SDL_Window*   g_window;
extern SDL_Renderer* g_renderer;
extern LTexture g_block_texture;
extern LTexture g_amiga_texture;

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 640;
const int PLAYER_VEL = 5;

#endif