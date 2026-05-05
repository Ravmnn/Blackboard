#include <raylib.h>

#include <blackboard/editor/canvas.hpp>




int main(int argc, char** argv)
{
    SetTraceLogLevel(LOG_WARNING);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    int monitor = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");


    {
        Canvas canvas;

        while (!WindowShouldClose())
        {
            canvas.update();
            canvas.draw();
        }
    }


    CloseWindow();

    return 0;
}