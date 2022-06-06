#ifndef __VPLAYER__
#define __VPLAYER__
#include <SDL2/SDL.h>
#include <string>
#include "texture.h"
#include "helpers.h"

class Player
{
public:
    static constexpr float PLAYER_VEL = 240.0f;

    Player();

    void handle_event(SDL_Event &e);

    void move(float time_step);

    void load_texture();

    void render();

    FRect get_bbox() { return m_box; }
    int get_width() { return m_box.w; } 
private:
    FRect m_box;
    LTexture m_texture;

    float m_vel_x, m_vel_y;
};
#endif