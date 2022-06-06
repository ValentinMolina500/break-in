#include <SDL2/SDL.h>
#include <string>

#include "player.h"
#include "globals.h"

Player::Player()
{
    m_box.w = 64;
    m_box.h = 16;
    m_box.x = (SCREEN_WIDTH - 64) / 2;
    m_box.y = 560;

    //Initialize the velocity
    m_vel_x = 0;
    m_vel_y = 0;
}

void Player::handle_event(SDL_Event &e)
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: m_vel_x -= PLAYER_VEL; break;
            case SDLK_RIGHT: m_vel_x += PLAYER_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: m_vel_x += PLAYER_VEL; break;
            case SDLK_RIGHT: m_vel_x -= PLAYER_VEL; break;
        }
    }
}

void Player::move(float timeStep)
{
      //Move the dot left or right
    m_box.x += m_vel_x * timeStep;

    //If the dot went too far to the left or right or touched a wall
    if( ( m_box.x < 0 ) || ( m_box.x + m_box.w > SCREEN_WIDTH ))
    {
        //move back
        if (m_box.x < 0)
        {
            m_box.x = 0;
        }
        else
        {
            m_box.x = SCREEN_WIDTH - m_box.w;

        }
    }

    //Move the dot up or down
    m_box.y += m_vel_y * timeStep;

    //If the dot went too far up or down or touched a wall
    if( ( m_box.y < 0 ) || ( m_box.y + m_box.h > SCREEN_HEIGHT ))
    {
        //move back
         m_box.y = SCREEN_HEIGHT - m_box.h;
    }
}

void Player::load_texture()
{
    // m_texture.loadFromFile("assets/player.png");
}
void Player::render()
{
    SDL_Rect clip;
    clip.w = 64;
    clip.h = 16;
    clip.x = 241;
    clip.y = 25;
    g_amiga_texture.render((int) m_box.x, (int) m_box.y, &clip);
}
