#include <blackboard/app.hpp>

#include <rlgl.h>

#include <rl_imgui.h>

#include <blackboard/debug/profiler.hpp>
#include <blackboard/debug/imgui_setup.hpp>
#include <blackboard/debug/profiler_imgui.hpp>
#include <blackboard/editor/editor.hpp>




using bb::App,
    bb::debug::IMGUISetup,
    bb::debug::Profiler,
    bb::debug::ProfilerIMGUI,
    bb::rendering::WindowRenderer,
    bb::ui::Context,
    bb::editor::Editor;




void App::initialize() noexcept
{
    SetTraceLogLevel(LOG_WARNING);

    initialize_window();
    initialize_app();
    initialize_imgui();
}


void App::initialize_window() noexcept
{
    const int monitor = GetCurrentMonitor();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");
    PollInputEvents();
}


void App::initialize_app() noexcept
{
    window_renderer = new WindowRenderer;
    window_renderer->use_buffer_texture = false;

    ui_context = new Context;
    editor = new Editor(*ui_context);
}


void App::initialize_imgui() noexcept
{
    rlImGuiSetup(true);

    IMGUISetup::setup_style();
}




void App::deinitialize() noexcept
{
    deinitialize_app();
    deinitialize_imgui();

    CloseWindow();
}


void App::deinitialize_app() noexcept
{
    delete window_renderer;
    delete ui_context;

    window_renderer = nullptr;
    ui_context = nullptr;
}


void App::deinitialize_imgui() noexcept
{
    rlImGuiShutdown();
}








void App::update() noexcept
{
    Profiler::begin("app::update");


    update_keybindings();

    rlDisableBackfaceCulling(); // IMGUI enables this every frame, so it also has to be disabled every frame

    ui_context->disable_mouse_input = ImGui::GetIO().WantCaptureMouse;
    ui_context->update();


    Profiler::end();
}


void App::update_keybindings() noexcept
{
    if (IsKeyPressed(KEY_F1)) ProfilerIMGUI::is_open = !ProfilerIMGUI::is_open;

    // TODO: move debug drawing from StrokeRendererRL to a separated class
    // if (IsKeyPressed(KEY_TWO)) editor->stroke_manager.renderer_rl.should_debug_draw_points = !editor->stroke_manager.renderer_rl.should_debug_draw_points;
    // if (IsKeyPressed(KEY_THREE)) editor->stroke_manager.renderer_rl.should_debug_draw_samples = !editor->stroke_manager.renderer_rl.should_debug_draw_samples;
    // if (IsKeyPressed(KEY_FOUR)) editor->stroke_manager.renderer_rl.should_debug_draw_edges = !editor->stroke_manager.renderer_rl.should_debug_draw_edges;
    if (IsKeyPressed(KEY_FIVE)) editor->wire_mode = !editor->wire_mode;
}




void App::draw() noexcept
{
    window_renderer->begin_render();

    Profiler::begin("app::draw");
        ui_context->draw();
    Profiler::end();

    draw_imgui();

    window_renderer->end_render();


    Profiler::reset();
}


void App::draw_imgui() noexcept
{
    rlImGuiBegin();
    ProfilerIMGUI::draw(*Profiler::root());
    rlImGuiEnd();
}