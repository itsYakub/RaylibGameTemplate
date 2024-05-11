// ------------------------------------------------------------------------------
// RaylibGameTemplate
// https://github.com/itsYakub/RaylibGameTemplate.git
// ------------------------------------------------------------------------------
// Author:
// https://github.com/itsYakub
// ------------------------------------------------------------------------------
// LICENCE (MIT):
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
// ------------------------------------------------------------------------------

#include <string>

#include "raylib.h"

#ifdef PLATFORM_WEB
    #include "emscripten.h"
#endif

// Function called on every frame. Handles the basic updating and rendering of the current game frame.
// (NOTE: c-style function is necessary for the emscritpen; it won't accept c++ methods)
// - void* args - the `Game` class instance.
void UpdateRenderFrame(void* args);

// The main game class.
class Game {
private:
    const int WIDTH; // Window width.
    const int HEIGHT; // Window width
    const std::string TITLE; // Window title.

public:
    // `Game` class constructor.
    Game() : WIDTH(1024), HEIGHT(768), TITLE(TextFormat("Raylib %s - Game %s", RAYLIB_VERSION, "1.0")) {
        // Setting the configuration flags.
        // (NOTE: They must be set before the window creation)
        SetConfigFlags(
            FLAG_VSYNC_HINT |
            FLAG_MSAA_4X_HINT |
            FLAG_WINDOW_RESIZABLE
        );

        // Initializing the Audio Device and creating a Window.
        InitAudioDevice();
        InitWindow(WIDTH, HEIGHT, TITLE.c_str());

#ifdef PLATFORM_WEB
        // Passing the `UpdateRenderFrame` function with the argument `this` for this `Game` class instance.
        // Value 0 caps the game's framerate to the default browser's framerate.
        // Value 1 tells emscritpen to simulate the infinite loop.
        emscripten_set_main_loop_arg(UpdateRenderFrame, this, 0, 1);
#else   
        while(!WindowShouldClose()) {
            UpdateRenderFrame(this);
        }
#endif

    }

    // `Game` class destructor.
    ~Game() {
        // Deinitializing the game's resources.
        CloseAudioDevice();
        CloseWindow();
    }

    // Update(): function is called on every game's cycle.
    // Purpose - update the internal components, logic, etc.
    void Update() {

    }

    // Render(): function is called on every game's cycle.
    // Purpose - render game's elements, components, text, etc.
    void Render() {
        ClearBackground(RAYWHITE);
    }
};

// Function called on every frame. Handles the basic updating and rendering of the current game frame.
// (NOTE: c-style function is necessary for the emscritpen; it won't accept c++ methods)
// - viod* args - the `Game` class instance.
void UpdateRenderFrame(void* args) {
    static_cast<Game*>(args)->Update();

    BeginDrawing();
    static_cast<Game*>(args)->Render();
    EndDrawing();
}

int main(int, char**) {
    // Creating the game instance.
    Game game;

    return 0;
}
