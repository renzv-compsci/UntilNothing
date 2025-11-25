// Main window for engine with lua initialization 

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "engine_lua.h"
#include <stdbool.h> 

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
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not render: %s\n", SDL_GetError());
    }

    success = engine_lua_init("game/scripts/main.lua");
    if (success) {
         engine_set_renderer(renderer);
    }

    int last_key_pressed = 0;
    engine_lua_update(last_key_pressed);

    int reload_key_pressed = 0; 
    engine_lua_update(reload_key_pressed); 

    // Main loop of the engine 
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                done = true;
            }

            if(event.type == SDL_EVENT_KEY_DOWN) {
                last_key_pressed = event.key.key;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_R && !reloading) {
                reload_requested = true; 
            }

            // perform reload once 
            if (reload_requested) {
                reloading = true; 
                engine_lua_shutdown();
            }
            success = engine_lua_init("game/scripts/main.lua");
            if (success) {
                engine_set_renderer(renderer);
                reload_requested = false;
                reloading = false; 
            }

            // gate per frame bridge calles with reloading flag per frame 
            if (!reloading) {
                engine_lua_update(last_key_pressed);
                last_key_pressed = 0;
            }

            // ignore key auto repeat 
            if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
                last_key_pressed = event.key.key;
                engine_lua_update(last_key_pressed);
                last_key_pressed = 0;
            }
        }
    }

    // This is the loop where u draw stuff
    SDL_SetRenderDrawColor(renderer, 102, 178, 255, 255); 
    SDL_RenderPresent(renderer);
    engine_lua_draw();
    SDL_RenderClear(renderer);

    // Close and destroy window 
    SDL_DestroyRenderer(renderer); // destroy renderer first before window 
    SDL_DestroyWindow(window);  
    SDL_Quit();
    return 0;
}