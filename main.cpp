#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <string>
#include <map>
#include <vector>

#include "globals.h"
#include "texture.h"
#include "ball.h"
#include "player.h"
#include "block.h"
#include "timer.h"

SDL_Window*   g_window;
SDL_Renderer* g_renderer;
LTexture g_amiga_texture;
LTexture g_block_texture;

std::vector<Block> blocks;
std::vector<Ball> balls;

// Init SDL and subsystems
bool init();

// Start the game!
void game_loop();

// Free memory
void cleanup();

// Place blocks on the screen
void init_blocks();

int main()
{
    // Init SDL
    if (!init())
    {
        printf("Could not init SDL!\n");
        return -1;
    }

    if (!g_block_texture.loadFromFile("assets/block.png"))
    {
        printf("Could not load block texture!\n");
        return -1;
    }
    
    if (!g_amiga_texture.loadFromFile("assets/amiga.png"))
    {
        printf("Could not load amiga texture!\n");
        return -1;
    }

    
    // Scale graphics for display
    int rw = 0, rh = 0;
    SDL_GetRendererOutputSize(g_renderer, &rw, &rh);
    if(rw != SCREEN_WIDTH) {
        float widthScale = (float)rw / (float) SCREEN_HEIGHT;
        float heightScale = (float)rh / (float) SCREEN_HEIGHT;

        if(widthScale != heightScale) {
            fprintf(stderr, "WARNING: width scale != height scale\n");
        }

        SDL_RenderSetScale(g_renderer, widthScale, heightScale);
    }

    init_blocks();

    game_loop();

    cleanup();

    return 0;
}

bool init()
{
    // Try initing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialized! SDL_GetError: %s\n", SDL_GetError());
        return false;
    }

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    // Create window
    g_window = SDL_CreateWindow(
        "BreakIN",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!g_window)
    {
        printf("SDL could not create window! SDL_GetError: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer for the window
    g_renderer = SDL_CreateRenderer(
        g_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!g_renderer)
    {
        printf("SDL could not create renderer! SDL_GetError: %s\n", SDL_GetError());
        return false;
    }

    // Initialize render options
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    // Initialize PNG loading
    int img_flags = IMG_INIT_PNG;
    if( !( IMG_Init( img_flags ) & img_flags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    return true;
}

void game_loop()
{
    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    Player player;
    player.load_texture();

    balls.push_back(Ball((SCREEN_WIDTH - 64 + 32 + 10) / 2, 300));

 

    //Keeps track of time between steps
    LTimer stepTimer;


    // Main loop    
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                 //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_e:
                        balls.push_back(Ball((SCREEN_WIDTH - 64 + 32 + 10) / 2, 300));
                        break;

                    default:
                        break;
                }
            }

            player.handle_event(e);
        } 

        //Calculate time step
		float timeStep = stepTimer.getTicks() / 1000.f;

        player.move(timeStep);

        // Handle collisions
        // ball.move(timeStep, player, blocks);
        for (auto& ball : balls)
        {
            ball.move(timeStep, player, blocks);
        }

        stepTimer.start();
       
        // Clear screen
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(g_renderer);   

        for (int i = 0; i < 320; i += 66)
        {
            for (int j = 0; j < 640; j += 64)
            {
                SDL_Rect clip;
                clip.x = 0;
                clip.y = 250;
                clip.w = 66;
                clip.h = 64;
                g_amiga_texture.render(i, j, &clip);
            }
        }
        


        // Render breakable blocks
        for (auto& block : blocks)
        {
            block.render();
        }

        for (auto& ball : balls)
        {
            ball.render();
        }

        

        player.render();
        // ball.render();

        // Update screen
        SDL_RenderPresent(g_renderer);
    }
}

void cleanup()
{
    SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	g_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void init_blocks()
{
    for (int i = 0; i < 320; i += 32)
    {
        for (int j = 0; j < 4; j++)
        {
            blocks.push_back(Block(i, j * 16));
        }
    }
}

