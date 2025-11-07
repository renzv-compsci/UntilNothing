// Main window for engine with lua initialization 

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "engine_lua.h"

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
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }
    engine_set_renderer(renderer);


    int last_key_pressed = 0;
    last_key_pressed = 0;
    engine_lua_update(last_key_pressed);
    engine_lua_init("game/scripts/main.lua");

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

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_R) {
                engine_lua_shutdown();
                engine_lua_init("game/scripts/main.lua");
                engine_set_renderer(renderer);
            }
            
        }
        // This is the loop where u draw stuff
        SDL_SetRenderDrawColor(renderer, 102, 178, 255, 255); 
        // SDL_RenderTexture(renderer, myTexture, NULL, NULL);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        // Call Lua functions 
        engine_lua_update(last_key_pressed); 
        engine_lua_draw(); 
    }
    // Close and destroy window 
    SDL_DestroyWindow(window);  
    SDL_DestroyRenderer(renderer);
    engine_lua_shutdown();
    SDL_Quit();
    return 0;
}