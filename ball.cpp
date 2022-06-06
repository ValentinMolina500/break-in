#include <stdio.h>

#include "ball.h"
#include "player.h"
#include "helpers.h"
#include "globals.h"
#include <gmtl/Math.h>

using namespace gmtl;

Ball::Ball(int x, int y)
{
    //Initialize the collision box
    mBox.x = x;
    mBox.y = y;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;
    current_speed = 240.0f;
    //Initialize the velocity
    mVelX = 0;
    mVelY = current_speed;
}

void Ball::move(float time_step, Player &player, std::vector<Block>& blocks)
{
    HitInfo hit_info;

    if (checkCollision(get_bbox(), player.get_bbox(), &hit_info))
    {
        // mVelY = -DOT_VEL;

        // TODO: add better bound logic

        // Arkanoid method
        int distance = player.get_width() - (hit_info.x + (get_bbox().w / 2));
        float angle = Math::PI / 4 -  (float) distance / player.get_width() * Math::PI / 2;
        
        mVelX = Math::cos(angle - Math::PI / 2) * current_speed;
        mVelY = Math::sin(angle - Math::PI / 2) * current_speed;
    }

    for (auto& block : blocks)
    {

        if (checkCollision(get_bbox(), block.get_bbox(), &hit_info) && !block.is_dead)
        {
            int distance = block.get_width() - (hit_info.x + (get_bbox().w / 2));
            float angle = Math::PI / 4 -  (float) distance / block.get_width() * Math::PI / 2;
            
            mVelX = -(Math::cos(angle - Math::PI / 2) * current_speed);
            mVelY = -(Math::sin(angle - Math::PI / 2) * current_speed);

            block.kill();
        }
    }
    

    // Ball went to high up
    if( ( mBox.y < 0 ))
    {
        //move back
        mBox.y = 0;
        mVelY = -mVelY;
    }
    else if (mBox.x < 0)
    {
        mBox.x = 0;
        mVelX = -mVelX;
    }
    else if (mBox.x > SCREEN_WIDTH - mBox.w)
    {
        mBox.x = SCREEN_WIDTH - mBox.w;
        mVelX = -mVelX;
    }

    //Move the Ball left or right
    mBox.x += mVelX * time_step;

    //Move the dot up or down
    mBox.y += mVelY * time_step;
}



void Ball::render()
{
    //Show the dot
    SDL_Rect clip;

    clip.w = 10;
    clip.h = 10;
    clip.x = 220;
    clip.y = 28;

	g_amiga_texture.render((int) mBox.x, (int) mBox.y, &clip);
}

void Ball::load_texture()
{
   // ball_texture.loadFromFile("assets/ball.png");
}