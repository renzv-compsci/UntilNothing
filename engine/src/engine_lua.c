#include "engine_lua.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <stdbool.h>

// static variables 
static lua_State *L = NULL; 
static SDL_Renderer *g_renderer = NULL; 
static bool has_update = false; 
static bool has_draw = false; 

static int l_engine_quit(lua_State *L);
static int l_engine_draw_rect(lua_State *L);

void engine_set_renderer(SDL_Renderer *r) {
    g_renderer = r;
}

bool engine_lua_init(const char* game_script_path) {

    // close prev state (if any)
    if (L) {
        lua_close(L);
        L = NULL;
        has_update = has_draw = false; 
    }

    // create new lua state
    L = luaL_newstate();
    if (!L) {
        fprintf(stderr, "luaL_newstate failed\n");
        return false; 
    }
    luaL_openlibs(L);

    // register engine table ONCE (replaced tow step approach)
    lua_newtable(L);
    lua_pushcfunction(L, l_engine_quit);
    lua_setfield(L, -2, "quit");
    lua_pushcfunction(L, l_engine_draw_rect);
    lua_setfield(L, -2, "draw_rect");
    lua_setglobal(L, "engine");


    // try load and run lua script 
    if (luaL_dofile(L, game_script_path) != LUA_OK) {
        // add constant char
        const char *msg = lua_tostring(L, -1);
       // print if error persists 
       fprintf(stderr, "Error loading lua script '%s' : %s\n", game_script_path, msg ? msg : "(no message)");
       lua_pop(L, 1);
       lua_close(L);
       L = NULL; 
       return false; 
    }

    lua_getglobal(L, "update");
    has_update = lua_isfunction(L, -1);
    lua_pop(L, 1);

    lua_getglobal(L, "draw");
    has_draw = lua_isfunction(L, -1);
    lua_pop(L, 1);

    return true; 
}

// call lua update function 
void engine_lua_update(int keycode) {
    // start of engine lue_update 
    if (!L || !has_update) return; 

    lua_getglobal(L, "update");
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return; 
    }

    lua_pushinteger(L, keycode);
    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        const char *err = lua_tostring(L, -1);
        fprintf(stderr, "Lua update error: %s\n", err ? err : "(no message)");
        lua_pop(L, 1);
    }
}

// call lua draw function
void engine_lua_draw(void) {
    // start of engine lua_draw
    if (!L || !has_draw) return; 

    lua_getglobal(L, "draw");
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return; 
    }

    if (lua_pcall(L, 0, 0 ,0) != LUA_OK) {
        const char * err = lua_tostring(L, -1);
        fprintf(stderr, "Lua draw error: %s\n", err ? err : "(no message)");
        lua_pop(L, 1);
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
        SDL_FRect rect = {(float)x, (float)y, (float)w, (float)h};
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
    has_update = has_draw = false; 
}