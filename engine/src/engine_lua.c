#include "engine_lua.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lua.h>
#include <stdio.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <stdbool.h>

static lua_State *L = NULL; 
static SDL_Renderer *g_renderer = NULL; 

static int l_engine_quit(lua_State *L);
static int l_engine_draw_rect(lua_State *L);

void engine_set_renderer(SDL_Renderer *r) {
    g_renderer = r;
}

bool engine_lua_init(const char* game_script_path) {

    // new lua state 
    L = luaL_newstate();
    luaL_openlibs(L);
    
    lua_newtable(L);
    lua_pushcfunction(L, l_engine_quit);
    lua_setfield(L, -2, "quit");
    lua_setglobal(L, "engine");

    lua_getglobal(L, "engine");
    if (lua_isnil(L, -1)) lua_newtable(L);
    lua_pushcfunction(L, l_engine_draw_rect);
    lua_setfield(L, -2, "draw_rect");
    lua_setglobal(L, "engine");

    // try load and run lua script 
    if (luaL_dofile(L, game_script_path) != LUA_OK) {
       // print if error persists 
       fprintf(stderr, "Error loading lua script %s\n", lua_tostring(L, -1));
       lua_pop(L, 1);
    }
}

// call lua update function 
void engine_lua_update(int keycode) {
    if (!L) return;  // run only if lua is initialized 

    bool has_update = false; 
    bool has_draw = false; 

    has_draw = lua_iscfunction(L, "update");
    has_update = lua_isfunction(L, "update");

    lua_getglobal(L, "update");
    if (lua_isfunction(L, -1)) {
        lua_pushinteger(L, keycode); // pass key
        if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
            fprintf(stderr, "Lua update error: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    } else {
        lua_pop(L, 1); // remove nonfunction from the stack 
        fprintf(stderr, "'update' is not a lua function", lua_tostring(L, -1));
    }

    // defensive early return
    if (L == NULL || !has_update) {
        return;
    }

    if (L == NULL || !has_draw) {
        return;
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

static int l_engine_quit(lua_State *L) {
    SDL_Event e = {0};
    e.type = SDL_EVENT_QUIT;
    SDL_PushEvent(&e);
    return 0;
}

static int l_engine_draw_rect(lua_State *L) {
    int x = luaL_checkinteger(L, 1), y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3), h = luaL_checkinteger(L, 4);
    if (g_renderer) {
        SDL_FRect rect = {x, y, w, h};
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(g_renderer, &rect);
    }
    return 0;
}

// shutdown 
void engine_lua_shutdown(void) {
    if (L) {
        lua_close(L);
        L = NULL; 
    }
}