#include <blackboard/editor/editor.hpp>




using bb::editor::Editor,
    bb::ui::Context,
    bb::rendering::WindowRenderer;




int main(int /*unused*/, char** /*unused*/)
{
    SetTraceLogLevel(LOG_WARNING);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    int monitor = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");
    PollInputEvents();

    {
        WindowRenderer window_renderer;
        window_renderer.use_buffer_texture = false;

        Context ui_context;
        Editor editor(ui_context);

        while (!WindowShouldClose())
        {
            ui_context.update();

            window_renderer.begin_render();
            ui_context.draw();
            window_renderer.end_render();
        }
    }

    CloseWindow();

    return 0;
}