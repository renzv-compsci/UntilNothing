// Main window for engine with lua initialization 
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "engine_lua.h"
#include <stdbool.h> 
#include <stdio.h>

// main entry point 
int main (int argc, char* argv[]) {

    // Declare pointer for window 
    SDL_Window *window;
    bool done = false; 

    // create renderer 
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapTex = NULL;
    SDL_Surface *bitmapSurface = NULL;

    int width = 640;
    int height = 480;

    // starts with reloading = false so engine is usable
    bool reloading = false; 
    bool reload_requested = false;
    bool success = false; 
    bool lua_ready = false; 

    int last_key_pressed = 0;
    
    // Initialize SDL 3 
    SDL_Init(SDL_INIT_VIDEO);

    // create parameters for window application
    window = SDL_CreateWindow(
        "Until Nothing Engine",
        width, 
        height, 
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Can not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    success = engine_lua_init("game/scripts/main.lua");
    if (success) {
        fprintf(stdout, "Lua initialized OK\n");
        engine_set_renderer(renderer);
        lua_ready = true; 
    } else {
        fprintf(stderr, "Lua init failed -- press R to retry\n");
    }

    // Main loop of the engine 
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
                if (event.key.key == SDLK_R && !reloading) {
                    reload_requested = true;
                } else {
                    last_key_pressed = event.key.key;
                }
            }
        }

        if (reload_requested) {
            reloading = true;

            // shutdown current state 
            engine_lua_shutdown();

            // tries to initialize fresh lua state 
            success = engine_lua_init("game/scripts/main.lua");
            if (success) {
                engine_set_renderer(renderer);
                lua_ready = true;
                fprintf(stdout, "Lua reload succeeded\n");
            } else {
                fprintf(stderr, "Lua reload failed -- press R to retry\n");
            }
            // clear the request flags 
            reload_requested = false;
            reloading = false; 
        }
        // gate per frame bridge calles with reloading flag per frame 
        if (!reloading && lua_ready) {
            engine_lua_update(last_key_pressed);
            last_key_pressed = 0;
        }

        // This is the loop where u draw stuff
        SDL_SetRenderDrawColor(renderer, 102, 178, 255, 255); 
        SDL_RenderClear(renderer);
        engine_lua_draw();
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

    // Close and destroy window 
    engine_lua_shutdown();
    SDL_DestroyRenderer(renderer); // destroy renderer first before window 
    SDL_DestroyWindow(window);  
    SDL_Quit();
    return 0;
}