// SDL3 + Lua starter for the engine

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

// define window size 
#define WINDOW_W 1280
#define WINDOW_H 720

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static lua_State *L = NULL;

// This function runs once at startup.
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("UntilNothing Engine", "1.0", "com.untlnothing.engine");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("UntilNothing", WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, 0);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return SDL_APP_FAILURE;
    }

    SDL_SetWindowTitle(window, "UntilNothing Engine");

    // Initialize LUA 
    L = luaL_newstate();
    if (!L) {
        SDL_Log("Failed to create Lua state");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return SDL_APP_FAILURE;
    }
    luaL_openlibs(L);

    const char *gamepath = "../game/scripts/main.lua";
    if (luaL_dofile(L, gamepath) != LUA_OK) {
        SDL_Log("Lua error: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    return SDL_APP_CONTINUE;  // carry on with the program!
}

// This function runs when a new event occurs
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // end the program
    }
    if (event->type == SDL_EVENT_KEY_DOWN) {
        SDL_Keycode key = event->key.key;
        if (key == SDLK_ESCAPE) {
            return SDL_APP_SUCCESS;
        }
    }
    return SDL_APP_CONTINUE;
}

// This function runs once per frame
SDL_AppResult SDL_AppIterate(void *appstate)
{
    // Simple clear and present
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    // TODO: render your engine scene here (you can expose drawing functions to Lua)

    SDL_RenderPresent(renderer);

    SDL_Delay(16); // ~60 FPS cap

    return SDL_APP_CONTINUE;
}

// This function runs once at shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if (L) lua_close(L);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}