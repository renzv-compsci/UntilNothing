// declares and list the function types, macros, and variables 

#ifndef ENGINE_LUA_H
#define ENGINE_LUA_H



// Initialize lua and load game script 
void engine_lua_init(const char* game_script_path);

// call lua update function 
void engine_lua_update(void);

// call lua draw function
void engine_lua_draw(void);

// shutdown and cleanup
void engine_lua_shutdown(void);

#endif