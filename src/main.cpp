#include <imgui.h>
#include <rl_imgui.h>

#include <blackboard/ui/context.hpp>
#include <blackboard/editor/editor.hpp>
#include <blackboard/rendering/window_renderer.hpp>

#include <rlgl.h>



// TODO: add profiler (IMGUI)


using bb::editor::Editor,
    bb::ui::Context,
    bb::rendering::WindowRenderer;




int main(int /*unused*/, char** /*unused*/)
{
    const int monitor = GetCurrentMonitor();

    SetTraceLogLevel(LOG_WARNING);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");
    PollInputEvents();


    {
        WindowRenderer window_renderer;
        window_renderer.use_buffer_texture = false;

        Context ui_context;
        new Editor(ui_context);


        rlImGuiSetup(true);

        while (!WindowShouldClose())
        {
            rlDisableBackfaceCulling(); // IMGUI enables this every frame, so it also have to be disabled every frame


            ui_context.update();

            window_renderer.begin_render();
            ui_context.draw();


            rlImGuiBegin();
            rlImGuiEnd();

            window_renderer.end_render();
        }

        rlImGuiShutdown();
    }

    CloseWindow();

    return 0;
}