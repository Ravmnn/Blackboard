#include <blackboard/editor/editor.hpp>




using bb::editor::Editor;




int main(int /*unused*/, char** /*unused*/)
{
    SetTraceLogLevel(LOG_WARNING);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    int monitor = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");
    PollInputEvents();

    {
        Editor editor;

        while (!WindowShouldClose())
        {
            editor.update();
            editor.draw();
        }
    }

    CloseWindow();

    return 0;
}