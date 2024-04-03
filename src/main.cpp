#include <string>

#include "raylib.h"

#ifdef PLATFORM_WEB
    #include "emscripten.h"
#endif

void UpdateRenderFrame(void* args);

class Game {
private:
    const int WIDTH;
    const int HEIGHT;
    const std::string TITLE;

public:
    Game() : WIDTH(1024), HEIGHT(768), TITLE(TextFormat("Raylib %s - Game %s", RAYLIB_VERSION, "1.0")) {
        SetConfigFlags(FLAG_MSAA_4X_HINT);

        InitAudioDevice();
        InitWindow(WIDTH, HEIGHT, TITLE.c_str());

#ifdef PLATFORM_WEB
        emscripten_set_main_loop_arg(UpdateRenderFrame, this, 0, 1);
#else   
        SetTargetFPS(60);
        while(!WindowShouldClose()) {
            Update();

            BeginDrawing();
            Render();
            EndDrawing();
        }
#endif

        CloseAudioDevice();
        CloseWindow();
    }

    void Update() {

    }

    void Render() {
        ClearBackground(RAYWHITE);
    }
};

void UpdateRenderFrame(void* args) {
    static_cast<Game*>(args)->Update();

    BeginDrawing();
    static_cast<Game*>(args)->Render();
    EndDrawing();
}

int main(int, char**) {
    Game game;

    return 0;
}
