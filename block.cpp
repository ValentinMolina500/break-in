#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "block.h"
#include "globals.h"

Block::Block(int x, int y)
{
    m_box.x = x;
    m_box.y = y;
    m_box.w = 32;
    m_box.h = 16;
    is_dead = false;
}

void Block::render()
{
    if (is_dead) 
        return;
    
    SDL_Rect clip;

    clip.x = 0;
    clip.y = 0;
    clip.w = 32;
    clip.h = 16;
    g_amiga_texture.render(m_box.x, m_box.y, &clip);
}

void Block::kill()
{
    is_dead = true;
}