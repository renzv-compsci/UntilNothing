# TODO - November 5, 2025

- [ ] Create and complete engine_lua.h 
    - [ ] write function prototypes 
        engine_lua_init(const char* script_path);
        engine_lua_update(void);
        engine_lua_draw(void);
        engine_lua_shutdown(void);

- [ ] Start engine_lua.c 
    - [ ] Include headers and set up a static lua_State *L;
    - [ ] Write the skeletons for each function 
        Initialize Lua (luaL_newstate(), luaL_openlibs())
        Load a script (luaL_dofile())
        Print/log an error if the script fails to load
            
- [ ] Create simple game.lua script for prototyping and testing