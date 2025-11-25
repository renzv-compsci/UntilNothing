# TODO - November 5, 2025

- [/] Create and complete engine_lua.h 
    - [/] write function prototypes 
        engine_lua_init(const char* script_path);
        engine_lua_update(void);
        engine_lua_draw(void);
        engine_lua_shutdown(void);

- [/] Start engine_lua.c 
    - [/] Include headers and set up a static lua_State *L;
    - [/] Write the skeletons for each function 
        Initialize Lua (luaL_newstate(), luaL_openlibs())
        Load a script (luaL_dofile())
        Print/log an error if the script fails to load
            
- [/] Create simple game.lua script for prototyping and testing

# TODO - November 7–8, 2025

## DAY 1: ENGINE SIDE
- [ ] **Input Handling**
    - [ ] Send SDL key press state from SDL (C) into Lua’s update function (e.g. call `update(key)` in Lua each frame)

- [ ] **Lua-C Interface Extensions**
    - [ ] Make a C function `engine.quit()` that Lua can call to exit the engine
    - [ ] Make a C function `engine.draw_rect(x, y, w, h)` that Lua can call to draw rectangles
    
- [ ] **Script Reload**
    - [ ] Add a "reload scripts at runtime" feature (when pressing ‘R’ in C, reload Lua script)

---

## DAY 2: GAME SIDE

- [ ] **Game Menus/States**
    - [ ] In Lua, create a simple menu with a “Play” button/text and switch to “Game” state on key press
    - [ ] Add “Game Over” or “Winner” state, with option to restart from Lua

- [ ] **Game Logic**
    - [ ] Make an interactive object: move a player square/shape with arrow keys (use key input from C)
    - [ ] Add a score or timer variable that’s updated/drawn each frame in Lua
    - [ ] Define basic win/lose conditions in Lua script

- [ ] **Engine Features (from Day 1)**
    - [ ] Use new exposed engine C functions (renderer, quit) from Lua for menus or the game
    - [ ] Draw UI elements and gameplay objects by calling `engine.draw_rect` etc from Lua

- [ ] **Script Enhancements**
    - [ ] Refactor Lua game state/logic to be clean and modular 
    - [ ] Add comments and structure to `main.lua` (or game script)