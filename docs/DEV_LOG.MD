# Devlog – Oct 28, 2025

- Set up the project folders and got the repo started
- Built Lua from source and got the DLL and static lib working with MinGW
- Wrote a simple C main to embed Lua
- Made a hello.lua script and called it from C – saw "Hello from Lua!" print!
- Learned how to ignore .exe, .dll, and build files with .gitignore
- Got the VSCode build task working
- First real commit and push—project’s ready to go!

## Oct 29, 2025

- Spent the day wrestling with SDL3 linking and finally got it into my project folder. Used a mix of AI help (shoutout to the assistant) and YouTube tutorials — copy/pasting paths, trying different .a/.dll combos, and a lot of trial-and-error.
- Fixed the classic "undefined reference" nonsense by making sure I had the right MinGW import libs and that my gcc command had the proper order and -L path. Felt like archaeology, but it worked.
- Did a tiny celebratory run: green window showed up. Pretty happy.

## Oct 30, 2025

- Dug into some systems architecture basics so this doesn’t bite me again:
  - Learned why `-I` tells the compiler where headers live and `-L` tells the linker where libs live.
  - Realized the order of arguments matters (source files before `-l` flags), and why an import library needs to match the headers.
  - Learned the point of a Makefile: automate build commands, keep flags consistent, and stop typing the same long gcc line every time.
- Added a simple Makefile and tweaked VSCode configs so builds and IntelliSense are happier. Small QoL wins.