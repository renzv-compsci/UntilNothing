#include "engine_lua.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lua.h>
#include <stdio.h>


static lua_State *L = NULL; 

void engine_lua_init(const char* game_script_path) {

    // new lua state 
    L = luaL_newstate();
    luaL_openlibs(L);

    // try load and run lua script 
    if (luaL_dofile(L, game_script_path) != LUA_OK) {
       // print if error persists 
       fprintf(stderr, "Error loading lua script %s\n", lua_tostring(L, -1));
       lua_pop(L, 1);
    }
}

// call lua update function 
void engine_lua_update(void) {
    if (!L) return;  // run only if lua is initialized 

    lua_getglobal(L, "update");
    if (lua_isfunction(L, -1)) {
        if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            fprintf(stderr, "Lua update error: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    } else {
        lua_pop(L, 1); // remove nonfunction from the stack 
        fprintf(stderr, "'update' is not a lua function", lua_tostring(L, -1));
    }
}

// call lua draw function
void engine_lua_draw(void) {
    if (!L) return; 

    lua_getglobal(L, "draw");
    if (lua_isfunction(L, -1)) {
        if(lua_pcall(L, 0, 0, 0) != LUA_OK) {
            
            fprintf(stderr, "Lua draw error: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    } else {
        lua_pop(L, 1); // remove nonfunction from the stack 
        fprintf(stderr, "'draw' is not a lua function", lua_tostring(L, -1));
    }
}

// shutdown 
void engine_lua_shutdown(void) {
    if (L) {
        lua_close(L);
        L = NULL; 
    }
}