-- Sample prototype for the game

-- declare local variable for printing updates 
local printed_update = false 
local printed_draw = false 

-- declare key constanst for readability 
local esc = 27 
local space = 32 

-- these functions are called each frame by main.c engine
function update(key) 
    -- print once 
    if not printed_update then 
        print("Game updated called! (once)")
        printed_update = true
    end 

    if key and key ~= 0 then 
        if key == esc then 
            engine.quit()
        elseif key == space then
            print("Space pressed")
        else
            print("Key pressed (code):", key)
        end 
    end 
end 


function draw() 
    if not printed_draw then 
        print("Game draw called! (once)")
        printed_draw = true
    end 
    -- draw rectangle (sample) 
    engine.draw_rect(100, 120, 50, 50)
end 