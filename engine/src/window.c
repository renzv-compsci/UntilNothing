#include "window.h"
#include <stdio.h>
#include <SDL3/SDL_events.h>

// file - local state 
static SDL_Window *g_window = NULL; 
static int g_screen_width = 640; 
static int g_screen_height = 480; 


// function heeader, declares function window_create 
// accepts arguments title, width, height
SDL_Window *window_create(const char *title, int width, int height) {

    // create window, and creates 3 arguments
    g_window = SDL_CreateWindow(
        title, 
        width, height, 
        // create opengl capable window | allow window to be resizable
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    // check if succes 
    if (!g_window) {
        fprintf(stderr, "SDL_CreateWindow failed %s\n", SDL_GetError());
        return NULL; 
    }
    
    // update stored width and height 
    g_screen_width = width;
    g_screen_height = height;

    // return created pointer to the caller 
    return g_window; 
}

// declares function window_destroy 
void window_destroy(void) {

    // check if g_window is non-null
    if (g_window) {
        SDL_DestroyWindow(g_window);
        g_window = NULL;
    }
}

// getter functions that returns width and height 
int window_get_width(void) {
    return g_screen_width;
}

int window_get_height(void) {
    return g_screen_height;
}

// this function is called from main event loop for every SDL_Event I poll
void window_handle_sdl_event(const SDL_Event *ev) {
    
    // defense check; if caller passed a null pointer it will crash :>>
    if (!ev) return;

    // checks if incoming event is a window event 
    if (ev -> type == SDL_WindowEvent && ev->window.event == SDL_WINDOWEVENT_RESIZED) {
        int w = 0, h = 0;
    }
}