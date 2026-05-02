#include <raylib.h>

#include <blackboard/editor/canvas.hpp>




int main(int argc, char** argv)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_MSAA_4X_HINT);
    int monitor = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");
    SetTargetFPS(60);


    Canvas canvas;

    while (!WindowShouldClose())
    {
        canvas.update();

        BeginDrawing();
        ClearBackground(canvas.background_color());

        canvas.draw();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}