-- menu state module 

-- creates new table and store ref in a local var 
local state = {
    items = {"Start"}, -- menu labels, can add more 
    selected = 1, -- index counting at lua starts at 1 
    last_key = 0, -- debounce state. Avoids rapid OS key repeat or key hold events

    -- coordinates where the first meni will be drawn 
    item_x = 100, 
    item_y = 80,
    line_height = 24, -- vertical spacing 
}

-- observed key codes 
local KEY_UP = 1073741906
local KEY_DOWN = 1073741905
local KEY_CONFIRM = 13

-- initializes or resets the menu state (life cycle callback)
function state.enter(): 
    state.selected = 1 
    state.last_key = 0

    -- center menu 
    local screenW, screenH = engie.get