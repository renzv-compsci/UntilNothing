all:
	gcc engine\src\main.c -I "C:\SDL\i686-w64-mingw32\include" -I "C:\LUA\lua-5.4.8\src" -L "C:\SDL\i686-w64-mingw32\lib" -L "C:\LUA\lua-5.4.8\src" -lSDL3 -llua54 -o .\main.exe
	gcc engine\src\main.c engine\src\engine_lua.c -I "C:\SDL\i686-w64-mingw32\include" -I "C:\LUA\lua-5.4.8\src" -L "C:\SDL\i686-w64-mingw32\lib" -L "C:\LUA\lua-5.4.8\src" -lSDL3 -llua54 -o .\main.exe