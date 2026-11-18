
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "DungeonGame.h"

using namespace std;

const int resX = 1000;
const int resY = 1000;

 /* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

static const char* ProjectName = "Dungeon Quest 2026";

static DungeonGame* Game;

static Uint64 now;
static Uint64 last;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{     
    SDL_SetAppMetadata(ProjectName, "1.0", "");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(ProjectName, resX, resY, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Game = new DungeonGame();
    if (Game == nullptr) std::cout << "[SDLStarter] Game is Null";

    Game->Awake(renderer);


    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        // keyboard events    
        if (event->key.scancode == SDL_SCANCODE_W)
        {
            Game->MoveCharacter(Game->Hero, Up);
        }
        if (event->key.scancode == SDL_SCANCODE_S)
        {
            Game->MoveCharacter(Game->Hero, Down);
        }
        if (event->key.scancode == SDL_SCANCODE_A)
        {
            Game->MoveCharacter(Game->Hero, Left);
        }
        if (event->key.scancode == SDL_SCANCODE_D)
        {
            Game->MoveCharacter(Game->Hero, Right);
        }

    }

    
    

    return SDL_APP_CONTINUE;  /* carry on with the program! */
    
}

/*  This function runs once per frame, and is the heart of the program.
    Think of this like Unity's Update() loop */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    last = now;
    now = SDL_GetPerformanceCounter();
    double deltaTime = (double)(now - last) / (double)SDL_GetPerformanceFrequency();

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    // Your Update code goes here.
    Game->Update(renderer, deltaTime);

    Game->Draw(renderer);

    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{    

    /* SDL will clean up the window/renderer for us. */
}