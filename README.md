# What is PolisEngine?
PolisEngine is an open-source game engine focusing on ECS and Lua scripting. Its goal is to be extremely fast through the use of the [EnTT](https://github.com/skypjack/entt) library and be extremely dynamic through a Lua scripting engine that uses [sol](https://github.com/ThePhD/sol2) to allow fast, easy access to engine components. Rendering is done using OpenGL.

# Building PolisEngine
To build, run the following in the root directory:

    cmake -B build
    cmake --build ./build
This will build the main project PolisEngine which creates the .exe and an auxiliary project to copy some default assets (such as rendering primitives) to the output. As of now, it builds only for 64-bit Windows but that can be changed in the future.

# Using PolisEngine
PolisEngine requires that a file named Main.lua is present in the directory of the .exe. This file is run by the engine as it's initializing and is the entry point for any game-specific logic.
If you find that your project needs more direct engine integration, all that would require changing is to remove the line `lua_bridger.RunMainFile(LUA_MAIN_FILE);` from `Engine::Init` and adding your own code in between `engine.Init();` and `engine.StartGameLoop()` in `main.cpp`.
There is a demo project included, to use it just copy `demo/` and `out/` to the same directory and run the .exe.
# Credits
This project uses the following libraries:
[Lua 5.4](https://www.lua.org/home.html)
[OpenGL](https://www.khronos.org/)
[EnTT](https://github.com/skypjack/entt)
[sol](https://github.com/ThePhD/sol2)
[GLEW](http://glew.sourceforge.net/)
[GLFW](https://www.glfw.org/)
[GLM](https://github.com/g-truc/glm)
[Freetype](https://www.freetype.org/) (under the FTL license)
[Yoga](https://github.com/facebook/yoga)

If the distribution of any of the 3rd-party code or builds violates licensing, please let me know and I will make the necessary changes.