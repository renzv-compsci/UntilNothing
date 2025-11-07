-- Sample prototype for the game 

function update(key) 
    print("Game updated called!")
    if key == 27 then 
        engine.quit() 
    end

    if key == 32 then 
        print("Space pressed")
    end 
end 

function draw() 
    print("Game draw called!")
    engine.draw_rect(100, 120, 50, 50)
end 