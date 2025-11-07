// declares and list the function types, macros, and variables 

#ifndef ENGINE_LUA_H
#define ENGINE_LUA_H
#include <SDL3/SDL.h>



// Initialize lua and load game script 
void engine_lua_init(const char* game_script_path);

void engine_set_renderer(SDL_Renderer *r);

// call lua update function 
void engine_lua_update(int keycode);

// call lua draw function
void engine_lua_draw(void);

// shutdown and cleanup
void engine_lua_shutdown(void);

#endif