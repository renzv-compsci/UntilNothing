#pragma once

#include <SDL3/SDL.h> /* include the SDL header your build uses */

/* Public API: declarations only */
#ifdef __cplusplus
extern "C" {
#endif

SDL_Window *window_create(const char *title, int width, int height);
void window_destroy(void);
int  window_get_width(void);
int  window_get_height(void);
void window_handle_sdl_event(const SDL_Event *ev);

#ifdef __cplusplus
}
#endif