#include <raylib.h>

#include <blackboard/editor/canvas.hpp>




int main(int argc, char** argv)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    int monitor = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");


    Canvas canvas;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(canvas.background_color());

        canvas.update();
        canvas.draw();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}